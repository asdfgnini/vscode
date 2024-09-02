/*
*********************************************************************************************************
*	                                  
*	ģ������ : ThreadX
*	�ļ����� : mian.c
*	��    �� : V1.0
*	˵    �� : ThreadX�������
*              ʵ��Ŀ�ģ�
*                1. ѧϰThreadX�������              
*              ʵ�����ݣ�
*                1. �����������¼�������ͨ�����°���K1����ͨ�����ڻ�RTT��ӡ�����ջʹ�����
*                    ===============================================================
*                      OS CPU Usage =  1.94%
*                    ===============================================================
*                       Prio StackSize CurStack MaxStack Taskname
*                        2     4092      383      391    App Task Start
*                        3     4092      543      659    App Msp Pro
*                        4     4092      391      391    App Task UserIF
*                        5     4092      543      659    App Task COM
*                       30     1020      519      519    App Task STAT
*                       31     1020      143       71    App Task IDLE
*                        0     1020      391      391    System Timer Thread                
*                    �����������ʹ��SecureCRT����H7-TOOL RTT�鿴��ӡ��Ϣ��
*                    App Task Start����  ������������������BSP����������
*                    App Task MspPro���� ����Ϣ��������δʹ�á�
*                    App Task UserIF���� ��������Ϣ����
*                    App Task COM����    ����������LED��˸��
*                    App Task STAT����   ��ͳ������
*                    App Task IDLE����   ����������
*                    System Timer Thread����ϵͳ��ʱ������
*                2. (1) �����õ�printf������ȫ��ͨ������App_Printfʵ�֡�
*                   (2) App_Printf���������ź����Ļ�������������Դ�������⡣
*                3. Ĭ���ϵ���ͨ�����ڴ�ӡ��Ϣ�����ʹ��RTT��ӡ��Ϣ
*                   (1) MDK AC5��MDK AC6��IARͨ��ʹ��bsp.h�ļ��еĺ궨��Ϊ1����
*                       #define Enable_RTTViewer  1
*                   (2) Embedded Studio����ʹ�ô˺궨��Ϊ0, ��ΪEmbedded Studio�������˵���״̬RTT��ʽ�鿴��
*              ʵ�������   
*                1. K1�������´�ӡ����ִ�������
*                2. K2�������¹�������App Task COM��
*                3. K3�������»ָ�����App Task COM��
*                4. ҡ��OK�������¸�λ����App Task COM��
*              ע�����
*                1. ��ʵ��Ĵ����������ʹ��SecureCRT����H7-TOOL RTT�鿴��ӡ��Ϣ��
*                2. ��ؽ��༭��������������TAB����Ϊ4���Ķ����ļ���Ҫ��������ʾ�����롣
*
*	�޸ļ�¼ :
*		�汾��   ����         ����            ˵��
*       V1.0    2021-04-18   Eric2013    1. ST�̼���1.9.0�汾
*                                        2. BSP������V1.2
*                                        3. ThreadX�汾V6.0.1
*                                       
*	Copyright (C), 2021-2030, ���������� www.armfly.com
*
*********************************************************************************************************
*/
#include "includes.h"        


/*
*********************************************************************************************************
*                                 �������ȼ�����ֵԽС���ȼ�Խ��
*********************************************************************************************************
*/
#define  APP_CFG_TASK_START_PRIO                          1u
#define  APP_CFG_TASK_MsgPro_PRIO                         3u
#define  APP_CFG_TASK_USER_IF_PRIO                        4u
#define  APP_CFG_TASK_STAT_PRIO                           30u
#define  APP_CFG_TASK_IDLE_PRIO                           31u


/*
*********************************************************************************************************
*                                    ����ջ��С����λ�ֽ�
*********************************************************************************************************
*/
#define  APP_CFG_TASK_START_STK_SIZE                    4096u
#define  APP_CFG_TASK_MsgPro_STK_SIZE                   4096u
#define  APP_CFG_TASK_USER_IF_STK_SIZE                  4096u
#define  APP_CFG_TASK_IDLE_STK_SIZE                  	1024u
#define  APP_CFG_TASK_STAT_STK_SIZE                  	1024u

/*
*********************************************************************************************************
*                                       ��̬ȫ�ֱ���
*********************************************************************************************************
*/                                                        
static  TX_THREAD   AppTaskStartTCB;
static  uint64_t    AppTaskStartStk[APP_CFG_TASK_START_STK_SIZE/8];

static  TX_THREAD   AppTaskMsgProTCB;
static  uint64_t    AppTaskMsgProStk[APP_CFG_TASK_MsgPro_STK_SIZE/8];

static  TX_THREAD   AppTaskUserIFTCB;
static  uint64_t    AppTaskUserIFStk[APP_CFG_TASK_USER_IF_STK_SIZE/8];

static  TX_THREAD   AppTaskIdleTCB;
static  uint64_t    AppTaskIdleStk[APP_CFG_TASK_IDLE_STK_SIZE/8];

static  TX_THREAD   AppTaskStatTCB;
static  uint64_t    AppTaskStatStk[APP_CFG_TASK_STAT_STK_SIZE/8];


/*
*********************************************************************************************************
*                                      ��������
*********************************************************************************************************
*/
static  void  AppTaskStart          (ULONG thread_input);
static  void  AppTaskMsgPro         (ULONG thread_input);
static  void  AppTaskUserIF         (ULONG thread_input);
static  void  AppTaskIDLE			(ULONG thread_input);
static  void  AppTaskStat			(ULONG thread_input);
static  void  App_Printf (const char *fmt, ...);
static  void  AppTaskCreate         (void);
static  void  DispTaskInfo          (void);
static  void  AppObjCreate          (void);
static  void  OSStatInit (void);

/*
*******************************************************************************************************
*                               ����
*******************************************************************************************************
*/
static  TX_MUTEX   AppPrintfSemp;	/* ����printf���� */


/* ͳ������ʹ�� */
__IO uint8_t   OSStatRdy;        /* ͳ�����������־ */
__IO uint32_t  OSIdleCtr;        /* ����������� */
__IO float     OSCPUUsage;       /* CPU�ٷֱ� */
uint32_t       OSIdleCtrMax;     /* 1�������Ŀ��м��� */
uint32_t       OSIdleCtrRun;     /* 1���ڿ�������ǰ���� */

/*
*********************************************************************************************************
*	�� �� ��: main
*	����˵��: ��׼c������ڡ�
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
int main(void)
{
//	SCB->VTOR = 0x90000000;
 	/* HAL�⣬MPU��Cache��ʱ�ӵ�ϵͳ��ʼ?*/
	System_init();

	/* �ں˿���ǰ�ر�HAL��ʱ���׼ */
	HAL_SuspendTick();
	
    /* ����ThreadX�ں� */
    tx_kernel_enter();

	while(1);
}

/*
*********************************************************************************************************
*	�� �� ��: tx_application_define
*	����˵��: ThreadXר�õ����񴴽���ͨ�������������
*	��    ��: first_unused_memory  δʹ�õĵ�ַ�ռ�
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void  tx_application_define(void *first_unused_memory)
{
	/*
	   ���ʵ������CPU������ͳ�ƵĻ����˺���������ʵ����������ͳ������Ϳ����������������ں���
	   AppTaskCreate���洴����
	*/
	/**************������������*********************/
    tx_thread_create(&AppTaskStartTCB,              /* ������ƿ��ַ */   
                       "App Task Start",              /* ������ */
                       AppTaskStart,                  /* ������������ַ */
                       0,                             /* ���ݸ�����Ĳ��� */
                       &AppTaskStartStk[0],            /* ��ջ����ַ */
                       APP_CFG_TASK_START_STK_SIZE,    /* ��ջ�ռ��С */  
                       APP_CFG_TASK_START_PRIO,        /* �������ȼ�*/
                       APP_CFG_TASK_START_PRIO,        /* ������ռ��ֵ */
                       TX_NO_TIME_SLICE,               /* ������ʱ��Ƭ */
                       TX_AUTO_START);                 /* �������������� */
   	   
	/**************����ͳ������*********************/
    tx_thread_create(&AppTaskStatTCB,               /* ������ƿ��ַ */    
                       "App Task STAT",              /* ������ */
                       AppTaskStat,                  /* ������������ַ */
                       0,                           /* ���ݸ�����Ĳ��� */
                       &AppTaskStatStk[0],           /* ��ջ����ַ */
                       APP_CFG_TASK_STAT_STK_SIZE,    /* ��ջ�ռ��С */  
                       APP_CFG_TASK_STAT_PRIO,        /* �������ȼ�*/
                       APP_CFG_TASK_STAT_PRIO,        /* ������ռ��ֵ */
                       TX_NO_TIME_SLICE,             /* ������ʱ��Ƭ */
                       TX_AUTO_START);               /* �������������� */
					   
				   
	/**************������������*********************/
    tx_thread_create(&AppTaskIdleTCB,               /* ������ƿ��ַ */    
                       "App Task IDLE",              /* ������ */
                       AppTaskIDLE,                  /* ������������ַ */
                       0,                           /* ���ݸ�����Ĳ��� */
                       &AppTaskIdleStk[0],           /* ��ջ����ַ */
                       APP_CFG_TASK_IDLE_STK_SIZE,    /* ��ջ�ռ��С */  
                       APP_CFG_TASK_IDLE_PRIO,        /* �������ȼ�*/
                       APP_CFG_TASK_IDLE_PRIO,        /* ������ռ��ֵ */
                       TX_NO_TIME_SLICE,             /* ������ʱ��Ƭ */
                       TX_AUTO_START);               /* �������������� */
                       
//   MX_USBX_Host_Init();
			   
}

/*
*********************************************************************************************************
*	�� �� ��: AppTaskStart
*	����˵��: ��������
*	��    ��: thread_input ���ڴ���������ʱ���ݵ��β�
*	�� �� ֵ: ��
	�� �� ��: 2
*********************************************************************************************************
*/
static  void  AppTaskStart (ULONG thread_input)
{
	(void)thread_input;

    
	/* ����ִ������ͳ�� */
	OSStatInit();

	/* �ں˿����󣬻ָ�HAL���ʱ���׼ */
    HAL_ResumeTick();
	
    /* �����ʼ�� */
    bsp_Init();


    MX_USBX_Host_Init();
	/* �������� */
    AppTaskCreate(); 

	/* ���������ͨ�Ż��� */
	AppObjCreate();	

    while (1)
	{  
		/* ��Ҫ�����Դ���ĳ��򣬶�Ӧ������̵��õ�SysTick_ISR */
        bsp_ProPer1ms();
		
        tx_thread_sleep(1);
    }
}


/*
*********************************************************************************************************
*	�� �� ��: AppTaskMsgPro
*	����˵��: ��Ϣ������δʹ��
*	��    ��: thread_input ���ڴ���������ʱ���ݵ��β�
*	�� �� ֵ: ��
	�� �� ��: 3
*********************************************************************************************************
*/
static void AppTaskMsgPro(ULONG thread_input)
{
	(void)thread_input;
		  
	while(1)
	{
		bsp_LedToggle(2);
		tx_thread_sleep(500);
	}   
}

/*
*********************************************************************************************************
*	�� �� ��: AppTaskUserIF
*	����˵��: ������Ϣ����
*	��    ��: thread_input ����������ʱ���ݵ��β�
*	�� �� ֵ: ��
	�� �� ��: 4
*********************************************************************************************************
*/
static void AppTaskUserIF(ULONG thread_input)
{
	uint8_t ucKeyCode;	/* �������� */
	
	(void)thread_input;
		  
	while(1)
	{        

		ucKeyCode = bsp_GetKey();
		
		if (ucKeyCode != KEY_NONE)
		{
			switch (ucKeyCode)
			{
				case KEY_DOWN_K1:			  /* K1������ӡ����ִ����� */
					 DispTaskInfo();
					break;
				
				default:                     /* �����ļ�ֵ������ */
					break;
			}
		}

        tx_thread_sleep(20);
	}
}

/*
*********************************************************************************************************
*	�� �� ��: AppTaskStatistic
*	����˵��: ͳ����������ʵ��CPU�����ʵ�ͳ�ơ�Ϊ�˲��Ը���׼ȷ�����Կ���ע�͵��õ�ȫ���жϿ���
*	��    ��: thread_input ����������ʱ���ݵ��β� 
*	�� �� ֵ: ��
*   �� �� ��: 30
*********************************************************************************************************
*/
void  OSStatInit (void)
{
	OSStatRdy = FALSE;
	
    tx_thread_sleep(2u);        /* ʱ��ͬ�� */
	
    //__disable_irq();
    OSIdleCtr    = 0uL;         /* ����м��� */
	//__enable_irq();
	
    tx_thread_sleep(100);       /* ͳ��100ms�ڣ������м��� */
	
   	//__disable_irq();
    OSIdleCtrMax = OSIdleCtr;   /* ���������м��� */
    OSStatRdy    = TRUE;
	//__enable_irq();
}

static void AppTaskStat(ULONG thread_input)
{
	(void)thread_input;

    while (OSStatRdy == FALSE) 
	{
        tx_thread_sleep(200);     /* �ȴ�ͳ��������� */
    }

    OSIdleCtrMax /= 100uL;
    if (OSIdleCtrMax == 0uL) 
	{
        OSCPUUsage = 0u;
    }
	
    //__disable_irq();
    OSIdleCtr = OSIdleCtrMax * 100uL;  /* ���ó�ʼCPU������ 0% */
	//__enable_irq();
	
    for (;;) 
	{
       // __disable_irq();
        OSIdleCtrRun = OSIdleCtr;    /* ���100ms�ڿ��м��� */
        OSIdleCtr    = 0uL;          /* ��λ���м��� */
       //	__enable_irq();            /* ����100ms�ڵ�CPU������ */
        OSCPUUsage   = (100uL - (float)OSIdleCtrRun / OSIdleCtrMax);
        tx_thread_sleep(100);        /* ÿ100msͳ��һ�� */
    }
}

/*
*********************************************************************************************************
*	�� �� ��: AppTaskIDLE
*	����˵��: ��������
*	��    ��: thread_input ����������ʱ���ݵ��β�
*	�� �� ֵ: ��
	�� �� ��: 31
*********************************************************************************************************
*/
static void AppTaskIDLE(ULONG thread_input)
{	
  TX_INTERRUPT_SAVE_AREA

  (void)thread_input;
	
  while(1)
  {
	   TX_DISABLE
       OSIdleCtr++;
	   TX_RESTORE
  }			  	 	       											   
}

/*
*********************************************************************************************************
*	�� �� ��: AppTaskCreate
*	����˵��: ����Ӧ������
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
static  void  AppTaskCreate (void)
{
	/**************����MsgPro����*********************/
    tx_thread_create(&AppTaskMsgProTCB,               /* ������ƿ��ַ */    
                       "App Msp Pro",                 /* ������ */
                       AppTaskMsgPro,                  /* ������������ַ */
                       0,                             /* ���ݸ�����Ĳ��� */
                       &AppTaskMsgProStk[0],            /* ��ջ����ַ */
                       APP_CFG_TASK_MsgPro_STK_SIZE,    /* ��ջ�ռ��С */  
                       APP_CFG_TASK_MsgPro_PRIO,        /* �������ȼ�*/
                       APP_CFG_TASK_MsgPro_PRIO,        /* ������ռ��ֵ */
                       TX_NO_TIME_SLICE,               /* ������ʱ��Ƭ */
                       TX_AUTO_START);                /* �������������� */
   

	/**************����USER IF����*********************/
    tx_thread_create(&AppTaskUserIFTCB,               /* ������ƿ��ַ */      
                       "App Task UserIF",              /* ������ */
                       AppTaskUserIF,                  /* ������������ַ */
                       0,                              /* ���ݸ�����Ĳ��� */
                       &AppTaskUserIFStk[0],            /* ��ջ����ַ */
                       APP_CFG_TASK_USER_IF_STK_SIZE,  /* ��ջ�ռ��С */  
                       APP_CFG_TASK_USER_IF_PRIO,      /* �������ȼ�*/
                       APP_CFG_TASK_USER_IF_PRIO,      /* ������ռ��ֵ */
                       TX_NO_TIME_SLICE,               /* ������ʱ��Ƭ */
                       TX_AUTO_START);                 /* �������������� */
                       
}

/*
*********************************************************************************************************
*	�� �� ��: AppObjCreate
*	����˵��: ��������ͨѶ
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
static  void  AppObjCreate (void)
{
	 /* ���������ź��� */
    tx_mutex_create(&AppPrintfSemp,"AppPrintfSemp",TX_NO_INHERIT);
}

/*
*********************************************************************************************************
*	�� �� ��: App_Printf
*	����˵��: �̰߳�ȫ��printf��ʽ		  			  
*	��    ��: ͬprintf�Ĳ�����
*             ��C�У����޷��г����ݺ���������ʵ�ε����ͺ���Ŀʱ,������ʡ�Ժ�ָ��������
*	�� �� ֵ: ��
*********************************************************************************************************
*/
static  void  App_Printf(const char *fmt, ...)
{
    char  buf_str[200 + 1]; /* �ر�ע�⣬���printf�ı����϶࣬ע��˾ֲ������Ĵ�С�Ƿ��� */
    va_list   v_args;


    va_start(v_args, fmt);
   (void)vsnprintf((char       *)&buf_str[0],
                   (size_t      ) sizeof(buf_str),
                   (char const *) fmt,
                                  v_args);
    va_end(v_args);

	/* ������� */
    tx_mutex_get(&AppPrintfSemp, TX_WAIT_FOREVER);

    printf("%s", buf_str);

    tx_mutex_put(&AppPrintfSemp);					 
}

/*
*********************************************************************************************************
*	�� �� ��: DispTaskInfo
*	����˵��: ��ThreadX������Ϣͨ�����ڴ�ӡ����
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
static void DispTaskInfo(void)
{
	TX_THREAD      *p_tcb;	        /* ����һ��������ƿ�ָ�� */

    p_tcb = &AppTaskStartTCB;
	
	/* ��ӡ���� */
	App_Printf("===============================================================\r\n");
	App_Printf("OS CPU Usage = %5.2f%%\r\n", OSCPUUsage);
	App_Printf("===============================================================\r\n");
	App_Printf(" �������ȼ� ����ջ��С ��ǰʹ��ջ  ���ջʹ��   ������\r\n");
	App_Printf("   Prio     StackSize   CurStack    MaxStack   Taskname\r\n");

	/* ������������б�TCB list)����ӡ���е���������ȼ������� */
	while (p_tcb != (TX_THREAD *)0) 
	{
		
		App_Printf("   %2d        %5d      %5d       %5d      %s\r\n", 
                    p_tcb->tx_thread_priority,
                    p_tcb->tx_thread_stack_size,
                    (int)p_tcb->tx_thread_stack_end - (int)p_tcb->tx_thread_stack_ptr,
                    (int)p_tcb->tx_thread_stack_end - (int)p_tcb->tx_thread_stack_highest_ptr,
                    p_tcb->tx_thread_name);


        p_tcb = p_tcb->tx_thread_created_next;

        if(p_tcb == &AppTaskStartTCB) break;
	}
}

/***************************** ���������� www.armfly.com (END OF FILE) *********************************/
