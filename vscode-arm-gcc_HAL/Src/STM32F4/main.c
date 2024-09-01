
#include "main.h"

int main(void)
{

    bsp_Init();

    bsp_StartAutoTimer(0, 1000);
    uint8_t ucKeyCode;		/* 按键代码 */

    while(1)
    {
        if(bsp_CheckTimer(0))
        {
            bsp_LedToggle(1);
            printf("123\r\n");
            printf("周锦涛\r\n");
            printf("%f\r\n",123.145);
        }
		/* 按键滤波和检测由后台systick中断服务程序实现，我们只需要调用bsp_GetKey读取键值即可。 */
		ucKeyCode = bsp_GetKey();	/* 读取键值, 无键按下时返回 KEY_NONE = 0 */
		if (ucKeyCode != KEY_NONE)
		{
			switch (ucKeyCode)
			{
				case KEY_DOWN_K1:			/* K1键按下 */
					printf("K1键按下\r\n");
					break;

				case KEY_UP_K1:				/* K1键弹起 */
					printf("K1键弹起\r\n");
					break;

				case KEY_DOWN_K2:			/* K2键按下 */
					printf("K2键按下\r\n");
					break;

				case KEY_UP_K2:				/* K2键弹起 */
					printf("K2键弹起\r\n");
					break;

				case KEY_DOWN_K3:			/* K3键按下 */
					printf("K3键按下\r\n");
					break;

				case KEY_UP_K3:				/* K3键弹起 */
					printf("K3键弹起\r\n");
					break;

				case JOY_DOWN_U:			/* 摇杆UP键按下 */
					printf("摇杆上键按下\r\n");
					break;

				case JOY_DOWN_D:			/* 摇杆DOWN键按下 */
					printf("摇杆下键按下\r\n");
					break;

				case JOY_DOWN_L:			/* 摇杆LEFT键按下 */
					printf("摇杆左键按下\r\n");
					break;
				
				case JOY_LONG_L:            /* 摇杆LEFT键长按 */
					printf("摇杆左键长按\r\n");
					break;

				case JOY_DOWN_R:			/* 摇杆RIGHT键按下 */
					printf("摇杆右键按下\r\n");
					break;
				
				case JOY_LONG_R:            /* 摇杆RIGHT键长按 */
					printf("摇杆右键长按\r\n");
					break;

				case JOY_DOWN_OK:			/* 摇杆OK键按下 */
					printf("摇杆OK键按下\r\n");
					break;

				case JOY_UP_OK:				/* 摇杆OK键弹起 */
					printf("摇杆OK键弹起\r\n");
					break;
                    
                case SYS_DOWN_K1K2:			/* 摇杆OK键弹起 */
					printf("K1和K2组合键按下\r\n");
					break;

				default:
					/* 其它的键值不处理 */
					break;
			}
		
    }


    }
}