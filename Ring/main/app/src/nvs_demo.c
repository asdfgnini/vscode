#include "../app.h"


void NVS_mutil_namespace_demo(void)
{
    const char *namespaces[] = {"namespace1", "namespace2"};
    size_t ns_count = 2;

    // 每个命名空间的键数组（动态长度）
    const char *keys_ns1[] = {"key1", "key2"};
    const char *keys_ns2[] = {"key1", "key3", "key4"};
    const char **keys[] = {keys_ns1, keys_ns2};

    // 每个命名空间的键数量
    size_t key_counts[] = {2, 3};

    // 每个命名空间的值数组和长度
    const char data_ns1_key1[] = "Hello";
    const char data_ns1_key2[] = "World";
    const char data_ns2_key1[] = "ESP";
    const char data_ns2_key3[] = "Open";
    const char data_ns2_key4[] = "NVS";

    const void *data_ns1[] = {data_ns1_key1, data_ns1_key2};
    const void *data_ns2[] = {data_ns2_key1, data_ns2_key3, data_ns2_key4};
    const void **data[] = {data_ns1, data_ns2};

    size_t lengths_ns1[] = {sizeof(data_ns1_key1), sizeof(data_ns1_key2)};
    size_t lengths_ns2[] = {sizeof(data_ns2_key1), sizeof(data_ns2_key3), sizeof(data_ns2_key4)};
    size_t *lengths[] = {lengths_ns1, lengths_ns2};


    esp_err_t err = bsp_set_data_to_multiple_namespaces(namespaces, ns_count, keys, key_counts, data, lengths);
    if (err == ESP_OK) {
        printf("Data written successfully to multiple namespaces.\n");
    } else {
        printf("Error writing data: %d\n", err);
    }

    vTaskDelay(pdMS_TO_TICKS(1000));

    // 每个命名空间的输出缓冲区和长度
    char buffer_ns1_key1[64], buffer_ns1_key2[64];
    char buffer_ns2_key1[64], buffer_ns2_key3[64], buffer_ns2_key4[64];

    void *buffers_ns1[] = {buffer_ns1_key1, buffer_ns1_key2};
    void *buffers_ns2[] = {buffer_ns2_key1, buffer_ns2_key3, buffer_ns2_key4};
    void **buffers[] = {buffers_ns1, buffers_ns2};

    size_t lengths_ns1_read[] = {sizeof(buffer_ns1_key1), sizeof(buffer_ns1_key2)};
    size_t lengths_ns2_read[] = {sizeof(buffer_ns2_key1), sizeof(buffer_ns2_key3), sizeof(buffer_ns2_key4)};
    size_t *lengths_read[] = {lengths_ns1_read, lengths_ns2_read};

    // 调用批量读取函数
    err = bsp_get_data_from_multiple_namespaces(namespaces, ns_count, keys, key_counts, buffers, lengths_read);
    if (err == ESP_OK) {
        printf("Namespace1, Key1: %s\n", buffer_ns1_key1);
        printf("Namespace1, Key2: %s\n", buffer_ns1_key2);
        printf("Namespace2, Key1: %s\n", buffer_ns2_key1);
        printf("Namespace2, Key3: %s\n", buffer_ns2_key3);
        printf("Namespace2, Key4: %s\n", buffer_ns2_key4);
    } else {
        printf("Error reading keys: %d\n", err);
    }
}

void NVS_mutil_data_demo(void)
{
    const char *keys[] = {"key1", "key2", "key3"};
    const char *values[] = {"value3", "value2", "value1"};

    bsp_set_multiple_strings_to_nvs("WIFI1",keys,values,sizeof(keys)/sizeof(keys[0]));

    vTaskDelay(pdMS_TO_TICKS(1000));

    char buffer1[64], buffer2[64], buffer3[64];
    void *buffers[] = {buffer1,buffer2,buffer3};
    size_t lengths[] = {sizeof(buffer1), sizeof(buffer2), sizeof(buffer3)};
    size_t count = 3;
    esp_err_t err = bsp_get_multiple_data_from_nvs("WIFI1", keys, buffers, lengths, count);
    if(err == ESP_OK)
    {
        for (size_t i = 0; i < count; i++) 
        {
            printf("Read key: %s, value: %s\n", keys[i], (char *)buffers[i]);
        }
    }
    else 
    {
        printf("Error reading multiple keys: %d\n", err);
    }
}