
#include "../app.h"

#define TCA9554  1
#define XL9555   0

#define LCD_CTRL_GPIO BIT(1)
void IIC_EXIO_DEMO()
{

#if TCA9554
    esp_tca9554_config_t pca_cfg = {
        .i2c_scl = GPIO_NUM_18,
        .i2c_sda = GPIO_NUM_17,
        .interrupt_output = -1,
    };
    tca9554_init(&pca_cfg);

    tca9554_set_io_config(LCD_CTRL_GPIO, TCA9554_IO_OUTPUT);

    tca9554_set_output_state(LCD_CTRL_GPIO, TCA9554_IO_LOW);

    tca9554_read_all();
#elif XL9555

    esp_xl9555_config_t pca_cfg = {
        .i2c_scl = GPIO_NUM_42,
        .i2c_sda = GPIO_NUM_41,
        .interrupt_output = -1,
    };

    xl9555_init(&pca_cfg);

    xl9555_set_io_config(BEEP_IO, XL9555_IO_OUTPUT);

    xl9555_set_output_state(BEEP_IO, XL9555_IO_LOW);
    vTaskDelay(pdMS_TO_TICKS(1000));
    xl9555_set_output_state(BEEP_IO, XL9555_IO_HIGH);

#endif
}