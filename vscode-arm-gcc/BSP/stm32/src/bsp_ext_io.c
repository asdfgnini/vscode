

#include "bsp.h"



#define  HC574_PORT	 *(uint32_t *)0x64001000

__IO uint32_t g_HC574;	/* ����74HC574�˿�״̬ */

static void HC574_ConfigGPIO(void);
static void HC574_ConfigFMC(void);

void bsp_InitExtIO(void)
{
	HC574_ConfigGPIO();
	HC574_ConfigFMC();
	
	g_HC574 = (NRF24L01_CE | VS1053_XDCS | LED1 | LED2 | LED3 | LED4);
	HC574_PORT = g_HC574;	/* дӲ���˿ڣ�����IO״̬ */
}

void HC574_SetPin(uint32_t _pin, uint8_t _value)
{
	if (_value == 0)
	{
		g_HC574 &= (~_pin);
	}
	else
	{
		g_HC574 |= _pin;
	}
	HC574_PORT = g_HC574;
}

uint8_t HC574_GetPin(uint32_t _pin)
{
	if (g_HC574 & _pin)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

static void HC574_ConfigGPIO(void)
{

	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD | RCC_AHB1Periph_GPIOE | RCC_AHB1Periph_GPIOG
			| RCC_AHB1Periph_GPIOH | RCC_AHB1Periph_GPIOI, ENABLE);

	RCC_AHB3PeriphClockCmd(RCC_AHB3Periph_FMC, ENABLE);

	GPIO_PinAFConfig(GPIOD, GPIO_PinSource0, GPIO_AF_FMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource1, GPIO_AF_FMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource4, GPIO_AF_FMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource5, GPIO_AF_FMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource8, GPIO_AF_FMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource9, GPIO_AF_FMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource10, GPIO_AF_FMC);	
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource14, GPIO_AF_FMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource15, GPIO_AF_FMC);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_5 |
	                            GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_14 |
	                            GPIO_Pin_15;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	/* ���� GPIOE ��ص�IOΪ�����������? */
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource7 , GPIO_AF_FMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource8 , GPIO_AF_FMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource9 , GPIO_AF_FMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource10 , GPIO_AF_FMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource11 , GPIO_AF_FMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource12 , GPIO_AF_FMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource13 , GPIO_AF_FMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource14 , GPIO_AF_FMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource15 , GPIO_AF_FMC);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 |
	                            GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 |
	                            GPIO_Pin_15;
	GPIO_Init(GPIOE, &GPIO_InitStructure);

	/* ���� GPIOG ��ص�IOΪ�����������? */
	GPIO_PinAFConfig(GPIOG, GPIO_PinSource0, GPIO_AF_FMC);
	GPIO_PinAFConfig(GPIOG, GPIO_PinSource1, GPIO_AF_FMC);
	GPIO_PinAFConfig(GPIOG, GPIO_PinSource9, GPIO_AF_FMC);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_9;
	GPIO_Init(GPIOG, &GPIO_InitStructure);

	/* ���� GPIOH ��ص�IOΪ�����������? */
	GPIO_PinAFConfig(GPIOH, GPIO_PinSource8, GPIO_AF_FMC);
	GPIO_PinAFConfig(GPIOH, GPIO_PinSource9, GPIO_AF_FMC);
	GPIO_PinAFConfig(GPIOH, GPIO_PinSource10, GPIO_AF_FMC);
	GPIO_PinAFConfig(GPIOH, GPIO_PinSource11, GPIO_AF_FMC);
	GPIO_PinAFConfig(GPIOH, GPIO_PinSource12, GPIO_AF_FMC);
	GPIO_PinAFConfig(GPIOH, GPIO_PinSource13, GPIO_AF_FMC);
	GPIO_PinAFConfig(GPIOH, GPIO_PinSource14, GPIO_AF_FMC);
	GPIO_PinAFConfig(GPIOH, GPIO_PinSource15, GPIO_AF_FMC);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12
						| GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_Init(GPIOH, &GPIO_InitStructure);

	/* ���� GPIOI ��ص�IOΪ�����������? */
	GPIO_PinAFConfig(GPIOI, GPIO_PinSource0, GPIO_AF_FMC);
	GPIO_PinAFConfig(GPIOI, GPIO_PinSource1, GPIO_AF_FMC);
	GPIO_PinAFConfig(GPIOI, GPIO_PinSource2, GPIO_AF_FMC);
	GPIO_PinAFConfig(GPIOI, GPIO_PinSource3, GPIO_AF_FMC);
	GPIO_PinAFConfig(GPIOI, GPIO_PinSource6, GPIO_AF_FMC);
	GPIO_PinAFConfig(GPIOI, GPIO_PinSource7, GPIO_AF_FMC);
	GPIO_PinAFConfig(GPIOI, GPIO_PinSource9, GPIO_AF_FMC);
	GPIO_PinAFConfig(GPIOI, GPIO_PinSource10, GPIO_AF_FMC);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_6
						| GPIO_Pin_7 | GPIO_Pin_9 | GPIO_Pin_10;
	GPIO_Init(GPIOI, &GPIO_InitStructure);
}

/*
*********************************************************************************************************
*	�� �� ��: HC574_ConfigFMC
*	����˵��: ����FMC���ڷ���ʱ��
*	��    ��:  ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
static void HC574_ConfigFMC(void)
{
	FMC_NORSRAMInitTypeDef  init;
	FMC_NORSRAMTimingInitTypeDef  timing;

	/*
		AD7606������?��(3.3Vʱ)��RD���źŵ͵�ƽ����������21ns���ߵ�ƽ������̿���?15ns��

		������������ ������������Ϊ�˺�ͬBANK��LCD������ͬ��ѡ��3-0-6-1-0-0
		3-0-5-1-0-0  : RD�߳���75ns�� �͵�ƽ����50ns.  1us���ڿɶ�ȡ8·�������ݵ��ڴ档
		1-0-1-1-0-0  : RD��75ns���͵�ƽִ��12ns���ң��½��ز��Ҳ12ns.  ���ݶ�ȡ��ȷ��
	*/
	/* FMC_Bank1_NORSRAM2 configuration */
	timing.FMC_AddressSetupTime = 3;
	timing.FMC_AddressHoldTime = 0;
	timing.FMC_DataSetupTime = 6;
	timing.FMC_BusTurnAroundDuration = 1;
	timing.FMC_CLKDivision = 0;
	timing.FMC_DataLatency = 0;
	timing.FMC_AccessMode = FMC_AccessMode_A;

	/*
	 LCD configured as follow:
	    - Data/Address MUX = Disable
	    - Memory Type = SRAM
	    - Data Width = 16bit
	    - Write Operation = Enable
	    - Extended Mode = Enable
	    - Asynchronous Wait = Disable
	*/
	init.FMC_Bank = FMC_Bank1_NORSRAM2;
	init.FMC_DataAddressMux = FMC_DataAddressMux_Disable;
	init.FMC_MemoryType = FMC_MemoryType_SRAM;
	init.FMC_MemoryDataWidth = FMC_NORSRAM_MemoryDataWidth_32b;	// FMC_NORSRAM_MemoryDataWidth_16b;  FMC_NORSRAM_MemoryDataWidth_32b
	init.FMC_BurstAccessMode = FMC_BurstAccessMode_Disable;
	init.FMC_WaitSignalPolarity = FMC_WaitSignalPolarity_Low;
	init.FMC_WrapMode = FMC_WrapMode_Disable;
	init.FMC_WaitSignalActive = FMC_WaitSignalActive_BeforeWaitState;
	init.FMC_WriteOperation = FMC_WriteOperation_Enable;
	init.FMC_WaitSignal = FMC_WaitSignal_Disable;
	init.FMC_ExtendedMode = FMC_ExtendedMode_Disable;
	init.FMC_AsynchronousWait = FMC_AsynchronousWait_Disable;	
	init.FMC_WriteBurst = FMC_WriteBurst_Disable;
	init.FMC_ContinousClock = FMC_CClock_SyncOnly;	//FMC_CClock_SyncAsync;	// FMC_CClock_SyncOnly;	/* 429��407���һ������? */

	init.FMC_ReadWriteTimingStruct = &timing;
	init.FMC_WriteTimingStruct = &timing;

	FMC_NORSRAMInit(&init);

	/* - BANK 1 (of NOR/SRAM Bank 1~4) is enabled */
	FMC_NORSRAMCmd(FMC_Bank1_NORSRAM2, ENABLE);
}

/***************************** ���������� www.armfly.com (END OF FILE) *********************************/
