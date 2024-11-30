/*
 * SPDX-FileCopyrightText: 2023-2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include <sys/param.h>
#include "esp_tls.h"
#include "esp_http_client.h"
#include "esp_log.h"
#include "cJSON.h"
#include <freertos/FreeRTOS.h>
#include <freertos/timers.h>

#include "http_get_weather.h"

static const char *TAG = "http_get_weather";

/* Allocates memory for a weather data structure on the heap */
weather_data_t *http_weather_data_create() 
{
    weather_data_t *weather_data = (weather_data_t *)heap_caps_malloc(sizeof(weather_data_t), MALLOC_CAP_SPIRAM);

    if (weather_data != NULL) {
        weather_data -> week        = (char *)heap_caps_malloc(WEATHER_STRING_SIZE * sizeof(char), MALLOC_CAP_SPIRAM);
        weather_data -> text        = (char *)heap_caps_malloc(WEATHER_STRING_SIZE * sizeof(char), MALLOC_CAP_SPIRAM);

        if (weather_data->week == NULL || weather_data->text == NULL ) {
            ESP_LOGE(TAG, "Allocate weather data failed");
            free(weather_data->week);
            free(weather_data->text);
            free(weather_data);
            return NULL;
        }
    } else {
        ESP_LOGE(TAG, "Allocate weather data failed");
        return NULL;
    }

    return weather_data;
}

/* Deallocates memory used by a weather data structure */
esp_err_t http_weather_data_delete(weather_data_t *weather_data)
{
    if (weather_data != NULL) {
        if (weather_data->week != NULL) {
            free(weather_data->week);
        }

        if (weather_data->text != NULL) {
            free(weather_data->text);
        }

        free(weather_data);
        return ESP_OK;
    } else {
        ESP_LOGE(TAG, "Weather data is NULL");
        return ESP_FAIL;
    }

    return ESP_OK;
}

/* Event handler for HTTP client events */
esp_err_t _http_event_handler(esp_http_client_event_t *evt)
{
    static char *output_buffer;  // Buffer to store response of http request from event handler
    static int output_len;       // Stores number of bytes read
    switch(evt->event_id) {
        case HTTP_EVENT_ERROR:
            ESP_LOGD(TAG, "HTTP_EVENT_ERROR");
            break;
        case HTTP_EVENT_ON_CONNECTED:
            ESP_LOGD(TAG, "HTTP_EVENT_ON_CONNECTED");
            break;
        case HTTP_EVENT_HEADER_SENT:
            ESP_LOGD(TAG, "HTTP_EVENT_HEADER_SENT");
            break;
        case HTTP_EVENT_ON_HEADER:
            ESP_LOGD(TAG, "HTTP_EVENT_ON_HEADER, key=%s, value=%s", evt->header_key, evt->header_value);
            break;
        case HTTP_EVENT_ON_DATA:
            ESP_LOGD(TAG, "HTTP_EVENT_ON_DATA, len=%d", evt->data_len);
            /*
             *  Check for chunked encoding is added as the URL for chunked encoding used in this example returns binary data.
             *  However, event handler can also be used in case chunked encoding is used.
             */
            if (!esp_http_client_is_chunked_response(evt->client)) {
                // If user_data buffer is configured, copy the response into the buffer
                int copy_len = 0;
                if (evt->user_data) {
                    copy_len = MIN(evt->data_len, (MAX_HTTP_OUTPUT_BUFFER - output_len));
                    if (copy_len) {
                        memcpy(evt->user_data + output_len, evt->data, copy_len);
                    }
                } else {
                    const int buffer_len = esp_http_client_get_content_length(evt->client);
                    if (output_buffer == NULL) {
                        output_buffer = (char *) malloc(buffer_len);
                        output_len = 0;
                        if (output_buffer == NULL) {
                            ESP_LOGE(TAG, "Failed to allocate memory for output buffer");
                            return ESP_FAIL;
                        }
                    }
                    copy_len = MIN(evt->data_len, (buffer_len - output_len));
                    if (copy_len) {
                        memcpy(output_buffer + output_len, evt->data, copy_len);
                    }
                }
                output_len += copy_len;
            }

            break;
        case HTTP_EVENT_ON_FINISH:
            ESP_LOGD(TAG, "HTTP_EVENT_ON_FINISH");
            if (output_buffer != NULL) {
                // Response is accumulated in output_buffer. Uncomment the below line to print the accumulated response
                // ESP_LOG_BUFFER_HEX(TAG, output_buffer, output_len);
                free(output_buffer);
                output_buffer = NULL;
            }
            output_len = 0;
            break;
        case HTTP_EVENT_DISCONNECTED:
            ESP_LOGI(TAG, "HTTP_EVENT_DISCONNECTED");
            int mbedtls_err = 0;
            esp_err_t err = esp_tls_get_and_clear_last_error((esp_tls_error_handle_t)evt->data, &mbedtls_err, NULL);
            if (err != 0) {
                ESP_LOGI(TAG, "Last esp error code: 0x%x", err);
                ESP_LOGI(TAG, "Last mbedtls failure: 0x%x", mbedtls_err);
            }
            if (output_buffer != NULL) {
                free(output_buffer);
                output_buffer = NULL;
            }
            output_len = 0;
            break;
        case HTTP_EVENT_REDIRECT:
            ESP_LOGD(TAG, "HTTP_EVENT_REDIRECT");
            esp_http_client_set_header(evt->client, "From", "user@example.com");
            esp_http_client_set_header(evt->client, "Accept", "text/html");
            esp_http_client_set_redirection(evt->client);
            break;
    }
    return ESP_OK;
}

static void http_phrase_json(const char *local_response_buffer, weather_data_t *weather_data)
{
    if (local_response_buffer == NULL || weather_data == NULL) {
        ESP_LOGE(TAG, "NULL pointer input");
        return;
    }

    /* Parse the JSON response */
    cJSON *cjson_root = cJSON_Parse(local_response_buffer);

    cJSON *result           = cJSON_GetObjectItem(cjson_root,"result");
    cJSON *now              = cJSON_GetObjectItem(result,"now");

    cJSON *forecasts        = cJSON_GetObjectItem(result,"forecasts");
    cJSON *today_forecast   = cJSON_GetArrayItem(forecasts, 0);

    /* Extract weather data from the JSON response */
    strncpy(weather_data->text, cJSON_GetObjectItem(now, "text")->valuestring, WEATHER_STRING_SIZE - 1);
    strncpy(weather_data->week, cJSON_GetObjectItem(today_forecast, "week")->valuestring, WEATHER_STRING_SIZE - 1);


    cJSON_Delete(cjson_root);

    /* Log the retrieved weather data */
    ESP_LOGI(TAG, "============================");
    ESP_LOGI(TAG, "天气: %s", weather_data->text);
    ESP_LOGI(TAG, "星期: %s", weather_data->week);
    ESP_LOGI(TAG, "============================");
}

/* Perform an HTTP GET request to fetch weather data */
esp_err_t http_get_with_url(const char* http_url, weather_data_t *weather_data)
{
    if (http_url == NULL || weather_data == NULL) {
        ESP_LOGE(TAG, "NULL pointer input");
        return ESP_FAIL;
    }

    /* Create local response buffer for the HTTP response */
    char *local_response_buffer = (char *)calloc(MAX_HTTP_OUTPUT_BUFFER, sizeof(char));

    if (local_response_buffer == NULL) {
        ESP_LOGE(TAG, "Local response buffer calloc failed");
        return ESP_FAIL;
    }

    /*  Configure the HTTP client with the URL and event handler */
    esp_http_client_config_t config = {
        .url                    = http_url,
        .event_handler          = _http_event_handler,
        .user_data              = local_response_buffer,        // Pass address of local buffer to get response
        .disable_auto_redirect  = true,
    };

    esp_http_client_handle_t http_client = esp_http_client_init(&config);
    if (http_client == NULL) {
        ESP_LOGE(TAG, "HTTP client init failed");
        goto err;
    }

    /* Perform an HTTP GET request */
    esp_err_t err = esp_http_client_perform(http_client);
    if (err == ESP_OK) {
        ESP_LOGI(TAG, "HTTP GET Status = %d, content_length = %"PRIu64,
                esp_http_client_get_status_code(http_client),
                esp_http_client_get_content_length(http_client));
    } else {
        ESP_LOGE(TAG, "HTTP GET request failed: %s", esp_err_to_name(err));
        esp_http_client_cleanup(http_client);
        goto err;
    }

    /* Phrase the JSON data returned from API address */
    http_phrase_json(local_response_buffer, weather_data);

    /* Release the resource */
    esp_http_client_cleanup(http_client);
    free(local_response_buffer);

    return ESP_OK;

err:
    free(local_response_buffer);
    return ESP_FAIL;
}