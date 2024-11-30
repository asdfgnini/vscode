#include <stdio.h>
#include "app/app.h"




static const char *TAG = "main";

void app_main(void)
{
    bsp_init();
    app_init();


    while(1)
    {
        Button_Process();
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

