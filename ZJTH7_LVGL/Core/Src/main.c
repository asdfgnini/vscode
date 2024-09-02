
#include "bsp.h"
#include "lvgl.h"
#include "lv_port_disp_template.h"
#include "lv_port_indev_template.h"
#include "lv_demos.h"



#if USE_FreeRTOS == 1
static void vTaskGUI(void *pvParameters);
static void vTaskStart(void *pvParameters);
static void vTaskLED(void *pvParameters);
static void AppTaskCreate (void);


static TaskHandle_t xHandleTaskLED = NULL;
static TaskHandle_t xHandleTaskStart = NULL;

static void vTaskGUI(void *pvParameters)
{
	lv_init();
	lv_port_disp_init(); 
	lv_port_indev_init();
	
#if LV_USE_DEMO_WIDGETS
    lv_demo_widgets();
#endif
	
	TickType_t xLastWakeTime;
	const TickType_t xFrequency = 5;

	HAL_ResumeTick();
	
	/* ��ȡ��ǰ��ϵͳʱ�� */
    xLastWakeTime = xTaskGetTickCount();

	while (1) 
	{
		lv_timer_handler();
		
		vTaskDelayUntil(&xLastWakeTime, xFrequency);
	}
}

static void vTaskStart(void *pvParameters)
{
	TickType_t xLastWakeTime;
	const TickType_t xFrequency = 1;

	HAL_ResumeTick();
	
	/* ��ȡ��ǰ��ϵͳʱ�� */
    xLastWakeTime = xTaskGetTickCount();
	
    while(1)
    {
		/* ��Ҫ�����Դ���ĳ��򣬶�Ӧ������̵��õ�SysTick_ISR */
		bsp_ProPer1ms();
		
		/* vTaskDelayUntil�Ǿ����ӳ٣�vTaskDelay������ӳ١�*/
        vTaskDelayUntil(&xLastWakeTime, xFrequency);
    }
}

static void vTaskLED(void *pvParameters)
{
    while(1)
    {
		bsp_LedToggle(2);
        vTaskDelay(200);
    }
}

static void AppTaskCreate (void)
{
	xTaskCreate(  vTaskGUI,             /* ������  */
                  "vTaskGUI",           /* ������    */
                  8192,                 /* ����ջ��С����λword��Ҳ����4�ֽ� */
                  NULL,                 /* �������  */
                  1,                    /* �������ȼ�*/
                  NULL );               /* ������  */
//	
//    xTaskCreate( vTaskTaskUserIF,   	/* ������  */
//                 "vTaskUserIF",     	/* ������    */
//                 512,               	/* ����ջ��С����λword��Ҳ����4�ֽ� */
//                 NULL,              	/* �������  */
//                 2,                 	/* �������ȼ�*/
//                 &xHandleTaskUserIF );  /* ������  */
	
	
	xTaskCreate( vTaskLED,    		/* ������  */
                 "vTaskLED",  		/* ������    */
                 512,         		/* ����ջ��С����λword��Ҳ����4�ֽ� */
                 NULL,        		/* �������  */
                 3,           		/* �������ȼ�*/
                 &xHandleTaskLED ); /* ������  */
	
//	xTaskCreate( vTaskMsgPro,     		/* ������  */
//                 "vTaskMsgPro",   		/* ������    */
//                 2048,             		/* ����ջ��С����λword��Ҳ����4�ֽ� */
//                 NULL,           		/* �������  */
//                 4,               		/* �������ȼ�*/
//                 &xHandleTaskMsgPro );  /* ������  */
//	
//	
	xTaskCreate( vTaskStart,     		/* ������  */
                 "vTaskStart",   		/* ������    */
                 512,            		/* ����ջ��С����λword��Ҳ����4�ֽ� */
                 NULL,           		/* �������  */
                 10,              		/* �������ȼ�*/
                 &xHandleTaskStart );   /* ������  */
}
#endif


int main(void)
{
	System_init();
#if USE_FreeRTOS == 1
	HAL_SuspendTick();
	__set_PRIMASK(1); 

#endif
	bsp_Init();
#if USE_FreeRTOS == 1
	AppTaskCreate();
    vTaskStartScheduler();
#endif

#if USE_FreeRTOS == 0
	bsp_StartAutoTimer(0,5);
	bsp_StartAutoTimer(1,500);
#endif
#if USE_FreeRTOS == 1
	while(1);
#endif
	
#if USE_FreeRTOS == 0
	lv_init();
	lv_port_disp_init(); 
	lv_port_indev_init();
	
#if LV_USE_DEMO_WIDGETS
    lv_demo_widgets();
#endif

	while(1)
	{
		bsp_Idle();
		if(bsp_CheckTimer(0))
		{
			lv_timer_handler();
		}
		if(bsp_CheckTimer(1))
		{
			bsp_LedToggle(1);
		}
	}
#endif
}


