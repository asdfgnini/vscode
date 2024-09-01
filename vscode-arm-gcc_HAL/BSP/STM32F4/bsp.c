
#include "bsp.h"

static void SystemClock_Config(void);

void bsp_Init(void)
{

	HAL_Init();


	SystemClock_Config();

	
#if Enable_EventRecorder == 1  
	/* ��ʼ��EventRecorder������ */
	EventRecorderInitialize(EventRecordAll, 1U);
	EventRecorderStart();
#endif
	
	bsp_InitKey();    	
	bsp_InitTimer();  	
	bsp_InitUart();		
	bsp_InitExtIO();    
	bsp_InitLed();    	
}


static void SystemClock_Config(void)
{
	RCC_ClkInitTypeDef RCC_ClkInitStruct;
	RCC_OscInitTypeDef RCC_OscInitStruct;

	
	/* оƬ�ڲ���LDO��ѹ������ĵ�ѹ��Χ��ѡ�õ�PWR_REGULATOR_VOLTAGE_SCALE1 */
	__HAL_RCC_PWR_CLK_ENABLE();
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

	/* ʹ��HSE����ѡ��HSE��ΪPLLʱ��Դ */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLM = 8;
	RCC_OscInitStruct.PLL.PLLN = 336;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
	RCC_OscInitStruct.PLL.PLLQ = 4;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
	{
        Error_Handler(__FILE__, __LINE__);
	}

	/* 
       ѡ��PLL�������Ϊϵͳʱ��
		HCLK = SYSCLK / 1  (AHB1Periph)
		PCLK2 = HCLK / 2   (APB2Periph)
		PCLK1 = HCLK / 4   (APB1Periph)
    */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
								  |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
	{
        Error_Handler(__FILE__, __LINE__);
	}

	__HAL_RCC_SYSCFG_CLK_ENABLE() ;

	HAL_EnableCompensationCell();
}


void Error_Handler(char *file, uint32_t line)
{
	if (line == 0)
	{
		return;
	}
	
	while(1)
	{
	}
}

void bsp_RunPer10ms(void)
{
	bsp_KeyScan10ms();
}


void bsp_RunPer1ms(void)
{
	
}

void bsp_Idle(void)
{
	/* --- ι�� */

	/* --- ��CPU�������ߣ���Systick��ʱ�жϻ��ѻ��������жϻ��� */

	/* ���� emWin ͼ�ο⣬���Բ���ͼ�ο���Ҫ����ѯ���� */
	//GUI_Exec();

	/* ���� uIP Э�飬���Բ���uip��ѯ���� */
	//TOUCH_CapScan();
}

