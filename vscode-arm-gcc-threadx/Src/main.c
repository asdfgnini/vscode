#include "main.h"

int main()
{
    tx_kernel_enter();
}

void  tx_application_define(void *first_unused_memory)
{
    VOID *memory_ptr;
    if (tx_byte_pool_create(&tx_app_byte_pool, "Tx App memory pool", tx_byte_pool_buffer, TX_APP_MEM_POOL_SIZE) != TX_SUCCESS)
    {
        Error_Handler();
    }
    else {
         memory_ptr = (VOID *)&tx_app_byte_pool;
        if (App_ThreadX_Init(memory_ptr) != TX_SUCCESS)
        {
            Error_Handler();
        }
    }
}

UINT App_ThreadX_Init(VOID *memory_ptr)
{
    UINT ret = TX_SUCCESS;
    TX_BYTE_POOL *byte_pool = (TX_BYTE_POOL*)memory_ptr;
    CHAR *pointer;

    if (tx_byte_allocate(byte_pool, (VOID **) &pointer,
                        APP_CFG_TASK_START_STK_SIZE, TX_NO_WAIT) != TX_SUCCESS)
    {
        ret = TX_POOL_ERROR;
    }

    /**************创建启动任务*********************/
    if(tx_thread_create(&AppTaskStartTCB,              /* 任务控制块地址 */   
                    "App Task Start",              /* 任务名 */
                    AppTaskStart,                  /* 启动任务函数地址 */
                    0,                             /* 传递给任务的参数 */
                    pointer,                        /* 堆栈基地址 */
                    APP_CFG_TASK_START_STK_SIZE,    /* 堆栈空间大小 */  
                    APP_CFG_TASK_START_PRIO,        /* 任务优先级*/
                    APP_CFG_TASK_START_PRIO,        /* 任务抢占阀值 */
                    TX_NO_TIME_SLICE,               /* 不开启时间片 */
                    TX_AUTO_START) != TX_SUCCESS)                 /* 创建后立即启动 */
    {
        ret = TX_THREAD_ERROR;
    }
    if (tx_byte_allocate(byte_pool, (VOID **) &pointer,
                    APP_CFG_TASK_COM_STK_SIZE, TX_NO_WAIT) != TX_SUCCESS)
    {
        ret = TX_POOL_ERROR;
    }
    /**************创建COM任务*********************/
    if(tx_thread_create(&AppTaskCOMTCB,               /* 任务控制块地址 */    
                       "App Task COM",              /* 任务名 */
                       AppTaskCOM,                  /* 启动任务函数地址 */
                       0,                           /* 传递给任务的参数 */
                       pointer,            /* 堆栈基地址 */
                       APP_CFG_TASK_COM_STK_SIZE,    /* 堆栈空间大小 */  
                       APP_CFG_TASK_COM_PRIO,        /* 任务优先级*/
                       APP_CFG_TASK_COM_PRIO,        /* 任务抢占阀值 */
                       TX_NO_TIME_SLICE,             /* 不开启时间片 */
                       TX_AUTO_START) != TX_SUCCESS)               /* 创建后立即启动 */
    {
        ret = TX_POOL_ERROR;
    }


    if (tx_byte_allocate(byte_pool, (VOID **) &pointer,
                    APP_CFG_TASK_USER_IF_STK_SIZE, TX_NO_WAIT) != TX_SUCCESS)
    {
        ret = TX_POOL_ERROR;
    }
    	/**************创建USER IF任务*********************/
    if(tx_thread_create(&AppTaskUserIFTCB,               /* 任务控制块地址 */      
                       "App Task UserIF",              /* 任务名 */
                       AppTaskUserIF,                  /* 启动任务函数地址 */
                       0,                              /* 传递给任务的参数 */
                       pointer,            /* 堆栈基地址 */
                       APP_CFG_TASK_USER_IF_STK_SIZE,  /* 堆栈空间大小 */  
                       APP_CFG_TASK_USER_IF_PRIO,      /* 任务优先级*/
                       APP_CFG_TASK_USER_IF_PRIO,      /* 任务抢占阀值 */
                       TX_NO_TIME_SLICE,               /* 不开启时间片 */
                       TX_AUTO_START) != TX_SUCCESS)                 /* 创建后立即启动 */
    {
        ret = TX_POOL_ERROR;
    }

    return ret;
}


static  void  AppTaskStart (ULONG thread_input)
{
	(void)thread_input;
    /* 外设初始化 */
    bsp_Init();
	
    while (1)
	{  
		/* 需要周期性处理的程序，对应裸机工程调用的SysTick_ISR */
        bsp_ProPer1ms();
        tx_thread_sleep(1);
    }
}

static void AppTaskCOM(ULONG thread_input)
{	
	(void)thread_input;
	
	while(1)
	{
		bsp_LedToggle(3);
        printf("你好周锦涛\r\n");
        printf("%f\r\n",3.14);
        printf("hello gcc\r\n");
		tx_thread_sleep(1000);
	} 			  	 	       											   
}

static void AppTaskUserIF(ULONG thread_input)
{
	uint8_t ucKeyCode;	/* 按键代码 */
	
	(void)thread_input;
		  
	while(1)
	{        
		ucKeyCode = bsp_GetKey();
		
		if (ucKeyCode != KEY_NONE)
		{
			switch (ucKeyCode)
			{
				case KEY_DOWN_K1:			  /* K1键按打印任务执行情况 */
					 BSP_Printf("欢迎使用\r\n");
					break;
				
				case KEY_DOWN_K2:			  /* K2键挂起任务AppTaskCOM */
					 BSP_Printf("AppTaskCOM任务挂起\r\n");
					 tx_thread_suspend(&AppTaskCOMTCB);
					break;
				
				case KEY_DOWN_K3:			  /* K3键恢复任务AppTaskCOM */
					 BSP_Printf("AppTaskCOM任务恢复\r\n");
					 tx_thread_resume(&AppTaskCOMTCB);
					break;
				
				case JOY_DOWN_OK:			  /*摇杆OK键按下，复位任务AppTaskCOM */
					 BSP_Printf("AppTaskCOM任务复位\r\n");
					 tx_thread_terminate(&AppTaskCOMTCB); /* 这三个函数要依次调用才正常 */
					 tx_thread_reset(&AppTaskCOMTCB);
					 tx_thread_resume(&AppTaskCOMTCB);
					break;
				
				default:                     /* 其他的键值不处理 */
					break;
			}
		}

        tx_thread_sleep(20);
	}
}

void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  bsp_LedOff(1);
  while (1)
  {
    bsp_LedToggle(2);
    bsp_DelayMS(1000);
  }
  /* USER CODE END Error_Handler_Debug */
}

