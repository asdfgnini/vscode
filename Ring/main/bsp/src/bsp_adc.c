#include "../bsp.h"

adc_oneshot_unit_handle_t unit_handle;

uint16_t touch_chart[][3] = 
{
{0, 280, 600}, //1键  2.25v     315
{1, 780, 1000}, //2键  1.12v     820
{2, 1100, 1400}, //3键  1.689v  1290
{3, 1500, 2100}, //4键  0.562v  1460
{4, 2200, 2600}, //5键  2.81v   2480
{5, 2800, 3200}, //5键  2.81v   2480
};


void bsp_InitAdc(void)
{
    adc_oneshot_unit_init_cfg_t unit_cfg = {
        .clk_src = ADC_RTC_CLK_SRC_DEFAULT, //默认时钟源
        .ulp_mode = ADC_ULP_MODE_DISABLE,   //不启用ULP
        .unit_id = ADC_UNIT_1               //使用ADC1
    };
    ESP_ERROR_CHECK(adc_oneshot_new_unit(&unit_cfg, &unit_handle));

    adc_oneshot_chan_cfg_t channel_initer = {
        .atten = ADC_ATTEN_DB_12,               // 11dB衰减
        .bitwidth = ADC_BITWIDTH_12             // 输出12bit
    };

    ESP_ERROR_CHECK(adc_oneshot_config_channel(unit_handle, ADC_BUTTON_CHANNEL, &channel_initer));
}

uint32_t bsp_adc_get_rawvalue_average(uint32_t ch,uint32_t times)
{
    uint32_t temp_value = 0;
    uint8_t t;

    for(t = 0; t < times; t++)
    {
        int adc_raw = 0;
        adc_oneshot_read(unit_handle,ch,&adc_raw);
        temp_value += adc_raw;
        vTaskDelay(pdMS_TO_TICKS(5));
    }
    return temp_value / times;
}



uint8_t bsp_adc_get_button(void)
{
    for(uint8_t i = 0; i < BSP_KEY_BUM;i++)
    {
        int adc_raw = 0;
        adc_oneshot_read(unit_handle,ADC_BUTTON_CHANNEL,&adc_raw);
        if(adc_raw >= touch_chart[i][1] && adc_raw <= touch_chart[i][2])
        {
            return i + 1;
        }
    }
    return 0;
}


