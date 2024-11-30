#ifndef BSP_BUTTON_H_
#define BSP_BUTTON_H_

#include "stdint.h"
#include "stdio.h"
#include "stdbool.h"

#define BUTTON_DEBUG 0 //是否打印按键相关信息
enum
{
    BT_NONE,
    BT1_DOWN,
    BT1_DOUBLE,
    BT1_LONG,
    BT1_LONGFREE,

    BT2_DOWN,
    BT2_DOUBLE,
    BT2_LONG,
    BT2_LONGFREE,

    BT3_DOWN,
    BT3_DOUBLE,
    BT3_LONG,
    BT3_LONGFREE,

    BT4_DOWN,
    BT4_DOUBLE,
    BT4_LONG,
    BT4_LONGFREE,

    BT5_DOWN,
    BT5_DOUBLE,
    BT5_LONG,
    BT5_LONGFREE,

    BT6_DOWN,
    BT6_DOUBLE,
    BT6_LONG,
    BT6_LONGFREE,
};


#define KEY_ON 1  /* 定义按钮按下的状态 */
#define KEY_OFF 0 /* 定义按钮未按下的状态 */

#define BTN_NAME_MAX 32 /* 定义按钮名称的最大长度为 32 字节 */

/* 
定义去抖时间为 40ms，按钮检测周期为 10ms。  
仅当检测到稳定的 40ms 状态变化时才认为是有效操作，以避免抖动对检测的影响。
*/

/* 
是否支持单击和双击同时触发的配置项。  
通过定义 `SINGLE_AND_DOUBLE_TRIGGER`，可以实现单击和双击事件同时存在的机制。  

注意事项：  
由于判断双击事件时需要检测两个单击之间的时间是否超出双击时间限制 `BUTTON_DOUBLE_TIME`，  
在启用该功能时，单击事件的触发可能会被延迟，直到双击检测超时为止。  

如果未定义 `SINGLE_AND_DOUBLE_TRIGGER`，程序在检测到单击后将忽略双击逻辑，仅触发一次单击事件。
*/
#define SINGLE_AND_DOUBLE_TRIGGER 1   //是否开启单击和双击共存机制

/* 
是否支持连续触发（即按钮长时间按下会连续触发多次事件）。  
通过定义 `CONTINUOS_TRIGGER`，可以忽略单击、双击和长按的逻辑，仅关注按钮的连续动作。  
*/
#define CONTINUOS_TRIGGER   0// 是否启用连续触发功能

/* 
是否支持长按释放后再触发一次事件的功能（长按释放事件）。  
如果定义了 `LONG_FREE_TRIGGER`，按钮长按释放时会产生额外的事件，  
可以结合 `BUTTON_LONG_CYCLE` 配置生成周期性的长按释放事件。  
*/
#define LONG_FREE_TRIGGER 0 /* 设置为 0，表示不启用长按释放功能 */

/* 
是否支持长按过程中只触发一次事件的功能。  
如果定义了 `LONG_FREE_ENABLE`，长按期间仅触发一次长按事件，而不会重复触发。  
*/
#define LONG_FREE_ENABLE 1 /* 设置为 1，表示启用长按一次触发功能 */

#ifndef BUTTON_DEBOUNCE_TIME
#define BUTTON_DEBOUNCE_TIME 5 /* 去抖时间 (n-1) * 检测周期 (ms) */
#endif

#ifndef BUTTON_CONTINUOS_CYCLE
#define BUTTON_CONTINUOS_CYCLE 1 /* 连续触发周期 (n-1) * 检测周期 (ms) */
#endif

#ifndef BUTTON_LONG_CYCLE
#define BUTTON_LONG_CYCLE 1 /* 长按周期 (n-1) * 检测周期 (ms) */
#endif

#ifndef BUTTON_DOUBLE_TIME
#define BUTTON_DOUBLE_TIME 10 /* 双击最大间隔时间 (n-1) * 检测周期 (ms)，建议范围为 200-600ms */
#endif

#ifndef BUTTON_LONG_TIME
#define BUTTON_LONG_TIME 20 /* 长按阈值时间 (n-1) * 检测周期 (ms)，超过此时间触发长按事件 */
#endif

#define TRIGGER_CB(event)            \
  if (btn->CallBack_Function[event]) \
  btn->CallBack_Function[event]((Button_t *)btn)

typedef void (*Button_CallBack)(void *); /* 定义回调函数指针 */

typedef enum
{
  BUTTON_DOWN = 0,           /* 按钮按下事件 */
  BUTTON_UP,                 /* 按钮释放事件 */
  BUTTON_DOUBLE,             /* 按钮双击事件 */
  BUTTON_LONG,               /* 按钮长按事件 */
  BUTTON_LONG_FREE,          /* 按钮长按后释放事件 */
  BUTTON_CONTINUOS,          /* 按钮连续按下事件 */
  BUTTON_CONTINUOS_FREE,     /* 按钮连续按下后释放事件 */
  BUTTON_ALL_RIGGER,         /* 所有按钮事件的触发标志 */
  number_of_event,           /* 可支持的按钮事件总数，用于回调函数数组的大小 */
  NONE_TRIGGER               /* 无触发事件，表示初始状态或无效事件 */
} Button_Event;


typedef struct button
{
  /* 定义一个函数指针，用于指向用户实现的按钮状态读取函数 */
  uint8_t (*Read_Button_Level)(void); /* 读取按钮电平值，需由用户自行实现 */

  char Name[BTN_NAME_MAX]; /* 按钮的名称，字符数组用于标识按钮，最大长度由宏定义 `BTN_NAME_MAX` 决定 */

  /* 使用位域表示按钮的各种状态 */
  uint8_t Button_State : 4;         /* 当前按钮状态，如按下、弹起等 */
  uint8_t Button_Last_State : 4;    /* 上一次的按钮状态，用于判断状态变化（如检测双击） */
  uint8_t Button_Trigger_Level : 2; /* 按钮触发的电平值（如低电平触发或高电平触发） */
  uint8_t Button_Last_Level : 2;    /* 按钮的上一次电平值，用于辅助判断按钮状态 */

  uint8_t Button_Trigger_Event; /* 按钮触发的事件，例如单击、双击或长按等事件类型 */

  Button_CallBack CallBack_Function[number_of_event]; /* 回调函数数组，用于处理按钮触发的不同事件 */

  uint8_t Button_Cycle; /* 按键的检测周期，用于确定按钮检测的频率 */

  uint8_t Timer_Count;   /* 计时器计数，用于延时或定时功能 */
  uint8_t Debounce_Time; /* 去抖时间，用于消除按钮按下/释放时的抖动 */

  uint8_t Long_Time; /* 长按时间阈值，超过此时间视为长按 */

  struct button *Next; /* 链表指针，用于连接多个按钮结构体，便于管理多个按钮 */

} Button_t;




void bsp_InitButton(void);

/**
 * @brief 创建一个按键对象，并初始化相关参数。
 * 
 * @param name 按键名称，用于标识按键（字符串形式）。
 * @param btn 指向按键对象的指针，用于存储按键信息。
 * @param read_btn_level 按键电平读取函数的指针，用于获取按键当前的高低电平状态。
 * @param btn_trigger_level 按键触发的电平级别（KEY_ON 或 KEY_OFF）。
 */
void Button_Create(const char *name,
                   Button_t *btn,
                   uint8_t (*read_btn_level)(void),
                   uint8_t btn_trigger_level);

/**
 * @brief 为指定按键的特定事件注册回调函数。
 * 
 * @param btn 指向按键对象的指针。
 * @param btn_event 按键事件类型，例如 BUTTON_DOWN、BUTTON_LONG 等。
 * @param btn_callback 回调函数指针，当对应事件触发时会调用该函数。
 */
void Button_Attach(Button_t *btn, Button_Event btn_event, Button_CallBack btn_callback);

/**
 * @brief 周期性处理单个按键的状态和事件检测。
 * 
 * @param btn 指向按键对象的指针。
 * 
 * @note 此函数需要在固定的时间周期内被调用，用于实现按键的状态检测与事件触发。
 */
void Button_Cycle_Process(Button_t *btn);

/**
 * @brief 处理所有按键的事件和状态。
 * 
 * @note 此函数会循环处理所有注册的按键对象，用于检测其状态并触发事件。
 */
void Button_Process(void);

/**
 * @brief 删除指定的按键对象，释放相关资源。
 * 
 * @param btn 指向要删除的按键对象的指针。
 */
void Button_Delete(Button_t *btn);

/**
 * @brief 搜索当前注册的按键列表。
 * 
 * @note 此函数可能用于调试或遍历按键链表以获取信息。
 */
void Search_Button(void);

/**
 * @brief 获取指定按键对象的事件信息。
 * 
 * @param btn 指向按键对象的指针。
 * 
 * @note 此函数用于调试或记录按键的事件历史。
 */
void Get_Button_EventInfo(Button_t *btn);

/**
 * @brief 获取指定按键的当前触发事件。
 * 
 * @param btn 指向按键对象的指针。
 * @return uint8_t 返回按键当前的事件类型。
 * 
 * @note 返回的事件类型可以是 BUTTON_DOWN、BUTTON_DOUBLE 等。
 */
uint8_t Get_Button_Event(Button_t *btn);

/**
 * @brief 获取指定按键的当前状态。
 * 
 * @param btn 指向按键对象的指针。
 * @return uint8_t 返回按键的当前状态（例如按下或释放）。
 */
uint8_t Get_Button_State(Button_t *btn);

/**
 * @brief 通用回调函数，用于处理按键触发的事件。
 * 
 * @param btn 按键对象的指针，用于区分触发事件的按键。
 * 
 * @note 用户可以在此函数中实现按键事件的统一处理逻辑。
 */
void Button_Process_CallBack(void *btn);


#endif

