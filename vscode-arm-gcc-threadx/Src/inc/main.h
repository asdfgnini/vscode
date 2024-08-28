#ifndef _MAIN_H_
#define _MAIN_H_

#include "bsp.h"



#include "tx_api.h"
#include "tx_timer.h"

extern void SysTick_ISR(void);
#define bsp_ProPer1ms  SysTick_ISR



/***********************************************/
//#define
/***********************************************/
//任务优先级
#define  APP_CFG_TASK_START_PRIO                          2u
#define  APP_CFG_TASK_COM_PRIO                            5u
#define  APP_CFG_TASK_USER_IF_PRIO                        4u

//任务栈大小
#define  APP_CFG_TASK_START_STK_SIZE                    4096/4u
#define  APP_CFG_TASK_COM_STK_SIZE                      4096/4u
#define  APP_CFG_TASK_USER_IF_STK_SIZE                  4096/4u

//任务控制块
static  TX_THREAD   AppTaskStartTCB;
static  TX_THREAD   AppTaskCOMTCB;
static  TX_THREAD   AppTaskUserIFTCB;

//任务执行函数
static  void  AppTaskStart          (ULONG thread_input);
static  void  AppTaskCOM			(ULONG thread_input);
static  void  AppTaskUserIF         (ULONG thread_input);


//错误处理函数
void Error_Handler(void);
//任务初始化函数，用于任务创建和组件创建
UINT App_ThreadX_Init(VOID *memory_ptr);

//Threadx 内存池大小
#define TX_APP_MEM_POOL_SIZE                     8 * 1024

//Threadx 内存池
static UCHAR tx_byte_pool_buffer[TX_APP_MEM_POOL_SIZE];
//内存池控制块
static TX_BYTE_POOL tx_app_byte_pool;


#endif

