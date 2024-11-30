
#include "../bsp.h"

//定义按键
Button_t Button_UP;
Button_t Button_ENTER;
Button_t Button_DOWN;
Button_t Button_RIGHT;
Button_t Button_LEFT;
Button_t Button_SIX;


uint8_t Button_Value = BT_NONE;

char * Button_Tips[]={
	"No Button!\n",
	"Button 1 down!\n",
	"Button 1 Double!\n",
	"Button 1 Long!\n",
	"Button 1 Long_Free!\n",
	
	"Button 2 down!\n",
	"Button 2 Double!\n",
	"Button 2 Long!\n",
	"Button 2 Long_Free!\n",

	"Button 3 down!\n",
	"Button 3 Double!\n",
	"Button 3 Long!\n",
	"Button 3 Long_Free!\n",

	"Button 4 down!\n",
	"Button 4 Double!\n",
	"Button 4 Long!\n",
	"Button 4 Long_Free!\n",

	"Button 5 down!\n",
	"Button 5 Double!\n",
	"Button 5 Long!\n",
	"Button 5 Long_Free!\n",

    "Button 6 down!\n",
	"Button 6 Double!\n",
	"Button 6 Long!\n",
	"Button 6 Long_Free!\n",
};
// 按键1按下回调函数
void Btn1_Down_CallBack(void *btn)
{
    Button_Value = BT1_DOWN; // 设置按键1的状态为按下
    printf("Button 1 down!\n"); // 打印按键1按下信息
}

// 按键1双击回调函数
void Btn1_Double_CallBack(void *btn)
{
    Button_Value = BT1_DOUBLE; // 设置按键1的状态为双击
    printf("Button 1 Double!\n"); // 打印按键1双击信息
}

// 按键1长按回调函数
void Btn1_Long_CallBack(void *btn)
{
    Button_Value = BT1_LONG; // 设置按键1的状态为长按
    printf("Button 1 Long!\n"); // 打印按键1长按信息
}

// 按键1长按释放回调函数
void Btn1_Long_Free_CallBack(void *btn)
{
    Button_Value = BT1_LONGFREE; // 设置按键1的状态为长按释放
    printf("Button 1 Long_Free!\n"); // 打印按键1长按释放信息
}

// 按键2按下回调函数
void Btn2_Down_CallBack(void *btn)
{
    Button_Value = BT2_DOWN; // 设置按键2的状态为按下
    printf("Button 2 down!\n"); // 打印按键2按下信息
}

// 按键2双击回调函数
void Btn2_Double_CallBack(void *btn)
{
    Button_Value = BT2_DOUBLE; // 设置按键2的状态为双击
    printf("Button 2 Double!\n"); // 打印按键2双击信息
}

// 按键2长按回调函数
void Btn2_Long_CallBack(void *btn)
{
    Button_Value = BT2_LONG; // 设置按键2的状态为长按
    printf("Button 2 Long!\n"); // 打印按键2长按信息
}

// 按键2长按释放回调函数
void Btn2_Long_Free_CallBack(void *btn)
{
    Button_Value = BT2_LONGFREE; // 设置按键2的状态为长按释放
    printf("Button 2 Long_Free!\n"); // 打印按键2长按释放信息
}

// 按键3按下回调函数
void Btn3_Down_CallBack(void *btn)
{
    Button_Value = BT3_DOWN; // 设置按键3的状态为按下
    printf("Button 3 down!\n"); // 打印按键3按下信息
}

// 按键3双击回调函数
void Btn3_Double_CallBack(void *btn)
{
    Button_Value = BT3_DOUBLE; // 设置按键3的状态为双击
    printf("Button 3 Double!\n"); // 打印按键3双击信息
}

// 按键3长按回调函数
void Btn3_Long_CallBack(void *btn)
{
    Button_Value = BT3_LONG; // 设置按键3的状态为长按
    printf("Button 3 Long!\n"); // 打印按键3长按信息
}

// 按键3长按释放回调函数
void Btn3_Long_Free_CallBack(void *btn)
{
    Button_Value = BT3_LONGFREE; // 设置按键3的状态为长按释放
    printf("Button 3 Long_Free!\n"); // 打印按键3长按释放信息
}

// 按键4按下回调函数
void Btn4_Down_CallBack(void *btn)
{
    Button_Value = BT4_DOWN; // 设置按键4的状态为按下
    printf("Button 4 down!\n"); // 打印按键4按下信息
}

// 按键4双击回调函数
void Btn4_Double_CallBack(void *btn)
{
    Button_Value = BT4_DOUBLE; // 设置按键4的状态为双击
    printf("Button 4 Double!\n"); // 打印按键4双击信息
}

// 按键4长按回调函数
void Btn4_Long_CallBack(void *btn)
{
    Button_Value = BT4_LONG; // 设置按键4的状态为长按
    printf("Button 4 Long!\n"); // 打印按键4长按信息
}

// 按键4长按释放回调函数
void Btn4_Long_Free_CallBack(void *btn)
{
    Button_Value = BT4_LONGFREE; // 设置按键4的状态为长按释放
    printf("Button 4 Long_Free!\n"); // 打印按键4长按释放信息
}

// 按键5按下回调函数
void Btn5_Down_CallBack(void *btn)
{
    Button_Value = BT5_DOWN; // 设置按键5的状态为按下
    printf("Button 5 down!\n"); // 打印按键5按下信息
}

// 按键5双击回调函数
void Btn5_Double_CallBack(void *btn)
{
    Button_Value = BT5_DOUBLE; // 设置按键5的状态为双击
    printf("Button 5 Double!\n"); // 打印按键5双击信息
}

// 按键5长按回调函数
void Btn5_Long_CallBack(void *btn)
{
    Button_Value = BT5_LONG; // 设置按键5的状态为长按
    printf("Button 5 Long!\n"); // 打印按键5长按信息
}

// 按键5长按释放回调函数
void Btn5_Long_Free_CallBack(void *btn)
{
    Button_Value = BT5_LONGFREE; // 设置按键5的状态为长按释放
    printf("Button 5 Long_Free!\n"); // 打印按键5长按释放信息
}

// 按键6按下回调函数
void Btn6_Down_CallBack(void *btn)
{
    Button_Value = BT6_DOWN; // 设置按键6的状态为按下
    printf("Button 6 down!\n"); // 打印按键6按下信息
}

// 按键6双击回调函数
void Btn6_Double_CallBack(void *btn)
{
    Button_Value = BT6_DOUBLE; // 设置按键6的状态为双击
    printf("Button 6 Double!\n"); // 打印按键6双击信息
}

// 按键6长按回调函数
void Btn6_Long_CallBack(void *btn)
{
    Button_Value = BT6_LONG; // 设置按键6的状态为长按
    printf("Button 6 Long!\n"); // 打印按键6长按信息
}

// 按键6长按释放回调函数
void Btn6_Long_Free_CallBack(void *btn)
{
    Button_Value = BT6_LONGFREE; // 设置按键6的状态为长按释放
    printf("Button 6 Long_Free!\n"); // 打印按键6长按释放信息
}

// 按键1电平读取函数
uint8_t Read_KEY1_Level(void)
{
    return (bsp_adc_get_button() == 1) ? 1 : 0; // 如果返回的按键编号为1，表示按键1被按下
}

// 按键2电平读取函数
uint8_t Read_KEY2_Level(void)
{
    return (bsp_adc_get_button() == 2) ? 1 : 0; // 如果返回的按键编号为2，表示按键2被按下
}

// 按键3电平读取函数
uint8_t Read_KEY3_Level(void)
{
    return (bsp_adc_get_button() == 3) ? 1 : 0; // 如果返回的按键编号为3，表示按键3被按下
}

// 按键4电平读取函数
uint8_t Read_KEY4_Level(void)
{
    return (bsp_adc_get_button() == 4) ? 1 : 0; // 如果返回的按键编号为4，表示按键4被按下
}

// 按键5电平读取函数
uint8_t Read_KEY5_Level(void)
{
    return (bsp_adc_get_button() == 5) ? 1 : 0; // 如果返回的按键编号为5，表示按键5被按下
}

// 按键6电平读取函数
uint8_t Read_KEY6_Level(void)
{
    return (bsp_adc_get_button() == 6) ? 1 : 0; // 如果返回的按键编号为6，表示按键6被按下
}

void bsp_InitButton(void)
{
    bsp_InitAdc();
    // 创建按钮 "Button_UP" 并设置其回调函数
    Button_Create("Button_UP", 
                &Button_UP, 
                Read_KEY1_Level, // 按键电平读取函数
                KEY_ON);         // 按键激活电平状态
    Button_Attach(&Button_UP, BUTTON_DOWN, Btn1_Down_CallBack);           // 按下事件回调
    Button_Attach(&Button_UP, BUTTON_DOUBLE, Btn1_Double_CallBack);       // 双击事件回调
    Button_Attach(&Button_UP, BUTTON_LONG, Btn1_Long_CallBack);           // 长按事件回调
    Button_Attach(&Button_UP, BUTTON_LONG_FREE, Btn1_Long_Free_CallBack); // 长按释放事件回调

    // 创建按钮 "Button_ENTER" 并设置其回调函数
    Button_Create("Button_ENTER",
                &Button_ENTER,
                Read_KEY2_Level, 
                KEY_ON);         
    Button_Attach(&Button_ENTER, BUTTON_DOWN, Btn2_Down_CallBack);        // 按下事件回调
    Button_Attach(&Button_ENTER, BUTTON_DOUBLE, Btn2_Double_CallBack);    // 双击事件回调
    Button_Attach(&Button_ENTER, BUTTON_LONG, Btn2_Long_CallBack);        // 长按事件回调
    Button_Attach(&Button_ENTER, BUTTON_LONG_FREE, Btn2_Long_Free_CallBack); // 长按释放事件回调

    // 创建按钮 "Button_DOWN" 并设置其回调函数
    Button_Create("Button_DOWN",
                &Button_DOWN,
                Read_KEY3_Level, 
                KEY_ON);         
    Button_Attach(&Button_DOWN, BUTTON_DOWN, Btn3_Down_CallBack);         // 按下事件回调
    Button_Attach(&Button_DOWN, BUTTON_DOUBLE, Btn3_Double_CallBack);     // 双击事件回调
    Button_Attach(&Button_DOWN, BUTTON_LONG, Btn3_Long_CallBack);         // 长按事件回调
    Button_Attach(&Button_DOWN, BUTTON_LONG_FREE, Btn3_Long_Free_CallBack); // 长按释放事件回调

    // 创建按钮 "Button_RIGHT" 并设置其回调函数
    Button_Create("Button_RIGHT",
                &Button_RIGHT,
                Read_KEY4_Level, 
                KEY_ON);         
    Button_Attach(&Button_RIGHT, BUTTON_DOWN, Btn4_Down_CallBack);        // 按下事件回调
    Button_Attach(&Button_RIGHT, BUTTON_DOUBLE, Btn4_Double_CallBack);    // 双击事件回调
    Button_Attach(&Button_RIGHT, BUTTON_LONG, Btn4_Long_CallBack);        // 长按事件回调
    Button_Attach(&Button_RIGHT, BUTTON_LONG_FREE, Btn4_Long_Free_CallBack); // 长按释放事件回调

    // 创建按钮 "Button_LEFT" 并设置其回调函数
    Button_Create("Button_LEFT",
                &Button_LEFT,
                Read_KEY5_Level, 
                KEY_ON);         
    Button_Attach(&Button_LEFT, BUTTON_DOWN, Btn5_Down_CallBack);         // 按下事件回调
    Button_Attach(&Button_LEFT, BUTTON_DOUBLE, Btn5_Double_CallBack);     // 双击事件回调
    Button_Attach(&Button_LEFT, BUTTON_LONG, Btn5_Long_CallBack);         // 长按事件回调
    Button_Attach(&Button_LEFT, BUTTON_LONG_FREE, Btn5_Long_Free_CallBack); // 长按释放事件回调

    // 创建按钮 "Button_SIX" 并设置其回调函数
    Button_Create("Button_SIX",
                &Button_SIX,
                Read_KEY6_Level, 
                KEY_ON);         
    Button_Attach(&Button_SIX, BUTTON_DOWN, Btn6_Down_CallBack);          // 按下事件回调
    Button_Attach(&Button_SIX, BUTTON_DOUBLE, Btn6_Double_CallBack);      // 双击事件回调
    Button_Attach(&Button_SIX, BUTTON_LONG, Btn6_Long_CallBack);          // 长按事件回调
    Button_Attach(&Button_SIX, BUTTON_LONG_FREE, Btn6_Long_Free_CallBack); // 长按释放事件回调

    // 获取各按钮的事件状态
    Get_Button_Event(&Button_UP);     // 检测 "Button_UP" 的事件
    Get_Button_Event(&Button_ENTER);  // 检测 "Button_ENTER" 的事件
    Get_Button_Event(&Button_DOWN);   // 检测 "Button_DOWN" 的事件
    Get_Button_Event(&Button_SIX);    // 检测 "Button_SIX" 的事件



}

/*
************************************************************************************************
************************************************************************************************
************************************************************************************************
************************************************************************************************
************************************************************************************************
************************************************************************************************
************************************************************************************************
*/
static struct button *Head_Button = NULL;
bool long_press = false;


static char *StrnCopy(char *dst, const char *src, uint32_t n);
static void Print_Btn_Info(Button_t *btn);
static void Add_Button(Button_t *btn);

void Button_Create(const char *name,
                   Button_t *btn,
                   uint8_t (*read_btn_level)(void),
                   uint8_t btn_trigger_level)
{
    if (btn == NULL) 
    {
        // 如果传入的按钮指针为空，则不进行任何操作。
        // 通常情况下，这里可以添加一些错误处理代码。
    }

    /* 
    清空按钮结构体中的数据以初始化结构体字段。 
    此代码被注释掉，可能是因为不希望覆盖用户在传入按钮之前已填充的数据。
    */
    // memset(btn, 0, sizeof(struct button)); 

    /* 
    拷贝按钮名称到按钮结构体的 `Name` 字段中，确保名称不会超过 `BTN_NAME_MAX` 的限制。 
    `StrnCopy` 是一个安全的字符串拷贝函数，用于避免缓冲区溢出。
    */
    StrnCopy(btn->Name, name, BTN_NAME_MAX); 

    /* 
    初始化按钮的状态和事件字段： 
    - `Button_State`：设置为 `NONE_TRIGGER`，表示按钮当前没有触发任何事件。
    - `Button_Last_State`：设置为 `NONE_TRIGGER`，表示上一次的按钮状态为空。
    - `Button_Trigger_Event`：设置为 `NONE_TRIGGER`，表示当前没有触发事件。
    */
    btn->Button_State = NONE_TRIGGER;                  
    btn->Button_Last_State = NONE_TRIGGER;             
    btn->Button_Trigger_Event = NONE_TRIGGER;          

    /* 
    将用户提供的按钮电平读取函数赋值给 `Read_Button_Level` 字段， 
    以便通过回调机制动态读取按钮的当前电平状态。
    */
    btn->Read_Button_Level = read_btn_level;           

    /* 
    设置按钮触发的电平值，通过 `btn_trigger_level` 确定按钮的触发条件（高电平或低电平触发）。
    */
    btn->Button_Trigger_Level = btn_trigger_level;     

    /* 
    读取按钮的当前电平值，并将其存储到 `Button_Last_Level` 字段中， 
    作为按钮初始化时的参考状态。
    */
    btn->Button_Last_Level = btn->Read_Button_Level(); 

    /* 
    初始化去抖时间字段为 0，表示当前没有去抖计时， 
    后续逻辑将根据状态变化更新去抖时间。
    */
    btn->Debounce_Time = 0; 

    /* 
    打印初始化成功的提示信息，帮助开发者确认按钮创建过程是否完成。
    */
#if BUTTON_DEBUG
    printf("Button create success!\r\n");
#endif
    /* 
    将初始化后的按钮结构体添加到按钮链表中，
    方便管理和遍历所有已注册的按钮。
    */
    Add_Button(btn); 

    /* 
    打印按钮的详细信息，包括名称、状态和相关配置，
    便于调试和验证按钮的初始化结果。
    */
#if BUTTON_DEBUG
    Print_Btn_Info(btn); 
#endif

}

void Button_Attach(Button_t *btn, Button_Event btn_event, Button_CallBack btn_callback)
{
    if (btn == NULL) 
    {
        // 如果传入的按钮指针为空，则直接返回，不执行任何操作。
        // 这通常是为了防止空指针引用导致程序崩溃。
    }

    /* 
    判断是否需要为所有事件设置回调函数。 
    `BUTTON_ALL_RIGGER` 是一个特殊的事件类型，用于标识 "所有事件" 的触发。 
    如果当前事件类型为 `BUTTON_ALL_RIGGER`，则为按钮的所有支持事件注册相同的回调函数。
    */
    if (BUTTON_ALL_RIGGER == btn_event) 
    {
        // 遍历所有支持的事件类型，为每个事件注册相同的回调函数。
        for (uint8_t i = 0; i < number_of_event - 1; i++) 
        {
            btn->CallBack_Function[i] = btn_callback; 
            // 将用户提供的 `btn_callback` 函数指针赋值给事件回调函数数组。
        }
    }
    else 
    {
        /* 
        如果不是 `BUTTON_ALL_RIGGER` 类型，则仅为指定的事件注册回调函数。 
        `btn_event` 指定了具体的事件类型，通过数组索引定位到该事件的回调函数位置。
        */
        btn->CallBack_Function[btn_event] = btn_callback; 
        // 将用户提供的 `btn_callback` 函数指针赋值给对应事件类型的回调函数。
    }
}

void Button_Delete(Button_t *btn)
{
    struct button **curr;
    for (curr = &Head_Button; *curr;)
    {
        struct button *entry = *curr;
        if (entry == btn)
        {
            *curr = entry->Next;
        }
        else
        {
            curr = &entry->Next;
        }
    }
}

void Get_Button_EventInfo(Button_t *btn)
{
    // 遍历按钮事件回调数组并打印事件类型（调试用）
    // 该循环用于检查按钮是否绑定了事件回调函数，并输出对应的事件编号
    for (uint8_t i = 0; i < number_of_event - 1; i++) // 遍历事件类型数组
    {
        if (btn->CallBack_Function[i] != 0) // 检查事件回调函数是否已绑定
        {
            printf("Button_Event:%d", i); // 打印事件编号（0: 按下，1: 双击，2: 长按，3: 长按释放等）
        }
    }
}

uint8_t Get_Button_Event(Button_t *btn)
{
    return (uint8_t)(btn->Button_Trigger_Event);
}

uint8_t Get_Button_State(Button_t *btn)
{
  return (uint8_t)(btn->Button_State);
}

void Button_Cycle_Process(Button_t *btn)
{
    uint8_t current_level = (uint8_t)btn->Read_Button_Level(); // 读取当前按键的电平状态

    // 检测按键电平是否发生变化
    if ((current_level != btn->Button_Last_Level) && (++(btn->Debounce_Time) >= BUTTON_DEBOUNCE_TIME))
    {
        btn->Button_Last_Level = current_level; // 更新按键的上一次电平状态
        btn->Debounce_Time = 0;                 // 消抖计时归零，确认当前状态有效

        // 按键从无触发状态或双击状态转变为按下状态
        if (((btn->Button_State == NONE_TRIGGER) || (btn->Button_State == BUTTON_DOUBLE)))
        {
            btn->Button_State = BUTTON_DOWN; // 切换状态为按下
        }
        // 按键从按下状态转变为释放状态
        else if (btn->Button_State == BUTTON_DOWN)
        {
            if (!long_press) // 如果不是长按释放
            {
                btn->Button_State = BUTTON_UP; // 切换状态为释放
                TRIGGER_CB(BUTTON_UP);         // 触发释放事件回调
            }
            else
            {
                long_press = false; // 重置长按标志
                btn->Button_State = BUTTON_UP;
                btn->Button_Trigger_Event = BUTTON_LONG_FREE; // 触发长按释放事件
            }
        }
    }

    // 根据当前按键状态执行不同的逻辑
    switch (btn->Button_State)
    {
        case BUTTON_DOWN: // 按下状态
        {
            if (btn->Button_Last_Level == btn->Button_Trigger_Level) // 检测按键触发电平
            {
#if CONTINUOS_TRIGGER // 是否支持连续触发

                if (++(btn->Button_Cycle) >= BUTTON_CONTINUOS_CYCLE)
                {
                    btn->Button_Cycle = 0;
                    btn->Button_Trigger_Event = BUTTON_CONTINUOS; // 触发连续按下事件
                    TRIGGER_CB(BUTTON_CONTINUOS);                 // 调用连续按下回调
                }

#else

                btn->Button_Trigger_Event = BUTTON_DOWN;

                if (++(btn->Long_Time) >= BUTTON_LONG_TIME) // 检测是否达到长按阈值
                {
#if LONG_FREE_TRIGGER // 是否支持长按释放触发

                    btn->Button_Trigger_Event = BUTTON_LONG;

#elif LONG_FREE_ENABLE
                    if (long_press == false)
                    {
                        TRIGGER_CB(BUTTON_LONG); // 触发长按事件
                        long_press = true;
                        btn->Button_Trigger_Event = BUTTON_LONG_FREE; // 切换为长按释放事件
                    }

#else

                    if (++(btn->Button_Cycle) >= BUTTON_LONG_CYCLE) // 检测是否支持长按持续触发
                    {
                        btn->Button_Cycle = 0;
                        btn->Button_Trigger_Event = BUTTON_LONG; // 触发长按事件
                        TRIGGER_CB(BUTTON_LONG);
                    }
#endif

                    if (btn->Long_Time == 0xFF) // 长按计时溢出时复位
                    {
                        btn->Long_Time = BUTTON_LONG_TIME;
                    }
                }

#endif
            }
            break;
        }

        case BUTTON_UP: // 按键释放状态
        {
            if (btn->Button_Trigger_Event == BUTTON_DOWN) // 如果触发了按下事件
            {
                if ((btn->Timer_Count <= BUTTON_DOUBLE_TIME) && (btn->Button_Last_State == BUTTON_DOUBLE)) // 检测双击
                {
                    btn->Button_Trigger_Event = BUTTON_DOUBLE;
                    TRIGGER_CB(BUTTON_DOUBLE); // 触发双击事件
                    btn->Button_State = NONE_TRIGGER; // 重置状态
                    btn->Button_Last_State = NONE_TRIGGER;
                }
                else
                {
                    btn->Timer_Count = 0;
                    btn->Long_Time = 0; // 检测长按失败，复位计时

#if (SINGLE_AND_DOUBLE_TRIGGER == 0)
                    TRIGGER_CB(BUTTON_DOWN); // 触发单击事件
#endif
                    btn->Button_State = BUTTON_DOUBLE;
                    btn->Button_Last_State = BUTTON_DOUBLE;
                }
            }
#if !LONG_FREE_ENABLE
            else if (btn->Button_Trigger_Event == BUTTON_LONG)
            {
#if LONG_FREE_TRIGGER
                TRIGGER_CB(BUTTON_LONG); // 触发长按事件
#endif
                btn->Long_Time = 0;
                btn->Button_State = NONE_TRIGGER;
                long_press = false;
                btn->Button_Last_State = BUTTON_LONG;
            }
#endif
            else if (btn->Button_Trigger_Event == BUTTON_LONG_FREE)
            {
#if LONG_FREE_ENABLE
                TRIGGER_CB(BUTTON_LONG_FREE); // 触发长按释放事件
#endif
                btn->Long_Time = 0;
                btn->Button_State = NONE_TRIGGER;
                long_press = false;
                btn->Button_Last_State = BUTTON_LONG_FREE;
            }
#if CONTINUOS_TRIGGER
            else if (btn->Button_Trigger_Event == BUTTON_CONTINUOS) // 连续按下释放
            {
                btn->Long_Time = 0;
                TRIGGER_CB(BUTTON_CONTINUOS_FREE); // 触发连续按下释放事件
                btn->Button_State = NONE_TRIGGER;
                btn->Button_Last_State = BUTTON_CONTINUOS;
            }
#endif
            break;
        }

        case BUTTON_DOUBLE: // 双击状态
        {
            btn->Timer_Count++; // 双击计时
            if (btn->Timer_Count >= BUTTON_DOUBLE_TIME)
            {
                btn->Button_State = NONE_TRIGGER; // 超时后复位状态
                btn->Button_Last_State = NONE_TRIGGER;
            }
#if SINGLE_AND_DOUBLE_TRIGGER
            if ((btn->Timer_Count >= BUTTON_DOUBLE_TIME) && (btn->Button_Last_State != BUTTON_DOWN))
            {
                btn->Timer_Count = 0;
                TRIGGER_CB(BUTTON_DOWN); // 触发单击事件
                btn->Button_State = NONE_TRIGGER;
                btn->Button_Last_State = BUTTON_DOWN;
            }
#endif
            break;
        }

        default:
            break;
    }
}

void Button_Process(void)
{
    struct button *pass_btn;
    for (pass_btn = Head_Button; pass_btn != NULL; pass_btn = pass_btn->Next)
    {
        Button_Cycle_Process(pass_btn);
    }
}

void Search_Button(void)
{
    struct button *pass_btn;
    for (pass_btn = Head_Button; pass_btn != NULL; pass_btn = pass_btn->Next)
    {
        printf("button node have %s \r\n", pass_btn->Name);
    }
}

static char *StrnCopy(char *dst, const char *src, uint32_t n)
{
    if (n != 0)
    {
        char *d = dst;
        const char *s = src;
        do
        {
            if ((*d++ = *s++) == 0)
            {
                while (--n != 0)
                    *d++ = 0;
                break;
            }
        } while (--n != 0);
    }
    return (dst);
}


static void Print_Btn_Info(Button_t *btn)
{

  printf("\nbutton struct information:\n\
              btn->Name:%s \n\
              btn->Button_State:%d \n\
              btn->Button_Trigger_Event:%d \n\
              btn->Button_Trigger_Level:%d \n\
              btn->Button_Last_Level:%d \n\n",
         btn->Name,
         btn->Button_State,
         btn->Button_Trigger_Event,
         btn->Button_Trigger_Level,
         btn->Button_Last_Level);
  Search_Button();
}



static void Add_Button(Button_t *btn)
{
  btn->Next = Head_Button;
  Head_Button = btn;
}