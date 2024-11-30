#ifndef _BSP_ADC_H_
#define _BSP_ADC_H_


#include <stdbool.h>
#include <stdint.h>
#include "esp_adc/adc_oneshot.h"
#include "hal/adc_types.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_adc/adc_cali.h"
#include "esp_adc/adc_cali_scheme.h"


//adc按键数量
#define BSP_KEY_BUM 6
//adc按键对应的adc通道
#define ADC_BUTTON_CHANNEL ADC_CHANNEL_4

void bsp_InitAdc(void);
uint32_t bsp_adc_get_rawvalue_average(uint32_t ch,uint32_t times);
uint8_t bsp_adc_get_button(void);

extern adc_oneshot_unit_handle_t unit_handle;

#endif

