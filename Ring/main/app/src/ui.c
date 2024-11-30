#include "../app.h"
#include "lvgl_helpers.h"
#include "lv_demos.h"
#include "esp_timer.h"

#define LCD_CTRL_GPIO BIT(1) // TCA9554_GPIO_NUM_1
#define LCD_RST_GPIO BIT(2)	 // TCA9554_GPIO_NUM_2
#define LCD_CS_GPIO BIT(3)	 // TCA9554_GPIO_NUM_2



static void lv_tick_task(void *arg)
{
	(void)arg;
	lv_tick_inc(10);
}
SemaphoreHandle_t xGuiSemaphore;


static void gui_task(void* arg)
{
    xGuiSemaphore = xSemaphoreCreateMutex();
    lv_init(); // lvgl内核初始化
	tca9554_set_output_state(LCD_RST_GPIO, TCA9554_IO_LOW);
	vTaskDelay(200 / portTICK_PERIOD_MS);
	tca9554_set_output_state(LCD_RST_GPIO, TCA9554_IO_HIGH);
	vTaskDelay(200 / portTICK_PERIOD_MS);

    lvgl_driver_init(); // lvgl显示接口初始化

    static lv_disp_draw_buf_t draw_buf;

	lv_color_t *buf1 = heap_caps_malloc(DISP_BUF_SIZE * 2, MALLOC_CAP_DMA);
	lv_color_t *buf2 = heap_caps_malloc(DISP_BUF_SIZE * 2, MALLOC_CAP_DMA);

	// lv_color_t *buf1 = (lv_color_t *)heap_caps_malloc(DISP_BUF_SIZE * 2, MALLOC_CAP_SPIRAM | MALLOC_CAP_8BIT);
	// lv_color_t *buf2 = (lv_color_t *)heap_caps_malloc(DISP_BUF_SIZE * 2, MALLOC_CAP_SPIRAM | MALLOC_CAP_8BIT);

	lv_disp_draw_buf_init(&draw_buf, buf1, buf2, DLV_HOR_RES_MAX * DLV_VER_RES_MAX); /*Initialize the display buffer*/

    static lv_disp_drv_t disp_drv;           /* 用于存储显示驱动的变量。必须是静态或全局变量 */
    lv_disp_drv_init(&disp_drv);              /* 基本初始化显示驱动 */
    disp_drv.draw_buf = &draw_buf;           /* 设置已初始化的缓冲区，用于存储绘制内容 */
    disp_drv.flush_cb = disp_driver_flush;   /* 设置刷新回调函数，用于将缓冲区内容绘制到显示屏 */
    disp_drv.hor_res = 280;                  /* 设置显示屏的水平分辨率，单位为像素 */
    disp_drv.ver_res = 240;                  /* 设置显示屏的垂直分辨率，单位为像素 */
    lv_disp_drv_register(&disp_drv);         /* 注册显示驱动，并保存创建的显示对象 */

    /*触摸屏输入接口配置*/
	lv_indev_drv_t indev_drv;
	lv_indev_drv_init(&indev_drv);
	indev_drv.read_cb = touch_driver_read;
	indev_drv.type = LV_INDEV_TYPE_POINTER;
	lv_indev_drv_register(&indev_drv);

    const esp_timer_create_args_t periodic_timer_args = {
		.callback = &lv_tick_task,
		.name = "periodic_gui"};
	esp_timer_handle_t periodic_timer;
	ESP_ERROR_CHECK(esp_timer_create(&periodic_timer_args, &periodic_timer));
	ESP_ERROR_CHECK(esp_timer_start_periodic(periodic_timer, 10 * 1000));

	lv_demo_widgets();

    while(1)
    {
        if (pdTRUE == xSemaphoreTake(xGuiSemaphore, portMAX_DELAY))
		{
			lv_timer_handler();
			xSemaphoreGive(xGuiSemaphore);
		}
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}



void ui_init(void)
{
        esp_tca9554_config_t pca_cfg = {
		.i2c_scl = GPIO_NUM_18,
		.i2c_sda = GPIO_NUM_17,
		.interrupt_output = -1,
	};
    
	tca9554_init(&pca_cfg);
	tca9554_set_io_config(LCD_CTRL_GPIO, TCA9554_IO_OUTPUT);
	tca9554_set_io_config(LCD_RST_GPIO, TCA9554_IO_OUTPUT);
	tca9554_set_output_state(LCD_CTRL_GPIO, TCA9554_IO_HIGH);

	tca9554_set_output_state(LCD_RST_GPIO, TCA9554_IO_LOW);
	vTaskDelay(200 / portTICK_PERIOD_MS);
	tca9554_set_output_state(LCD_RST_GPIO, TCA9554_IO_HIGH);
	vTaskDelay(200 / portTICK_PERIOD_MS);

    
	xTaskCreatePinnedToCore(gui_task, "gui task", 1024 * 4, NULL, 8, NULL, 1);


}