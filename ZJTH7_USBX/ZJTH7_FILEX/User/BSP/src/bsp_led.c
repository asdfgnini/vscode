

#include "bsp.h"


/* LED�ڶ�Ӧ��RCCʱ�� */
#define LED_GPIO_CLK_ALLENABLE() {	\
		__HAL_RCC_GPIOA_CLK_ENABLE();	\
		__HAL_RCC_GPIOB_CLK_ENABLE();	\
	};

	
#define GPIO_PORT_LED1  GPIOA
#define GPIO_PIN_LED1	GPIO_PIN_3

#define GPIO_PORT_LED2  GPIOB
#define GPIO_PIN_LED2	GPIO_PIN_0

#define GPIO_PORT_LED3  GPIOB
#define GPIO_PIN_LED3	GPIO_PIN_1


/*
*********************************************************************************************************
*	�� �� ��: bsp_InitLed
*	����˵��: ����LEDָʾ����ص�GPIO,  �ú����� bsp_Init() ���á�
*	��    ��:  ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void bsp_InitLed(void)
{
	GPIO_InitTypeDef  GPIO_InitStruct;

	/* ��GPIOʱ�� */
	LED_GPIO_CLK_ALLENABLE();
	
	bsp_LedOff(1);
	bsp_LedOff(2);
	bsp_LedOff(3);

	/* ����LED */
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;   		
	GPIO_InitStruct.Pull = GPIO_NOPULL;                 
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;  		

	GPIO_InitStruct.Pin = GPIO_PIN_LED1;
	HAL_GPIO_Init(GPIO_PORT_LED1, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = GPIO_PIN_LED2;
	HAL_GPIO_Init(GPIO_PORT_LED2, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = GPIO_PIN_LED3;
	HAL_GPIO_Init(GPIO_PORT_LED3, &GPIO_InitStruct);
}

/*
*********************************************************************************************************
*	�� �� ��: bsp_LedOn
*	����˵��: ����ָ����LEDָʾ�ơ�
*	��    ��:  _no : ָʾ����ţ���Χ 1 - 4
*	�� �� ֵ: ��
*********************************************************************************************************
*/

void bsp_LedOff(uint8_t _no)
{
	_no--;

	if (_no == 0)
	{
		HAL_GPIO_WritePin(GPIO_PORT_LED1,GPIO_PIN_LED1,GPIO_PIN_SET);
	}
	else if (_no == 1)
	{
		HAL_GPIO_WritePin(GPIO_PORT_LED2,GPIO_PIN_LED2,GPIO_PIN_SET);
	}
	else if (_no == 2)
	{
		HAL_GPIO_WritePin(GPIO_PORT_LED3,GPIO_PIN_LED3,GPIO_PIN_SET);
	}
}

/*
*********************************************************************************************************
*	�� �� ��: bsp_LedOff
*	����˵��: Ϩ��ָ����LEDָʾ�ơ�
*	��    ��:  _no : ָʾ����ţ���Χ 1 - 4
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void bsp_LedOn(uint8_t _no)
{
	_no--;

	if (_no == 0)
	{
		HAL_GPIO_WritePin(GPIO_PORT_LED1,GPIO_PIN_LED1,GPIO_PIN_RESET);
	}
	else if (_no == 1)
	{
		HAL_GPIO_WritePin(GPIO_PORT_LED1,GPIO_PIN_LED1,GPIO_PIN_RESET);
	}
	else if (_no == 2)
	{
		HAL_GPIO_WritePin(GPIO_PORT_LED1,GPIO_PIN_LED1,GPIO_PIN_RESET);
	}
}

/*
*********************************************************************************************************
*	�� �� ��: bsp_LedToggle
*	����˵��: ��תָ����LEDָʾ�ơ�
*	��    ��:  _no : ָʾ����ţ���Χ 1 - 4
*	�� �� ֵ: ��������
*********************************************************************************************************
*/
void bsp_LedToggle(uint8_t _no)
{
	if (_no == 1)
	{
		HAL_GPIO_TogglePin(GPIO_PORT_LED1,GPIO_PIN_LED1);
	}
	else if (_no == 2)
	{
		HAL_GPIO_TogglePin(GPIO_PORT_LED2,GPIO_PIN_LED2);
	}
	else if (_no == 3)
	{
		HAL_GPIO_TogglePin(GPIO_PORT_LED3,GPIO_PIN_LED3);
	}
}
/*
*********************************************************************************************************
*	�� �� ��: bsp_IsLedOn
*	����˵��: �ж�LEDָʾ���Ƿ��Ѿ�������
*	��    ��:  _no : ָʾ����ţ���Χ 1 - 4
*	�� �� ֵ: 1��ʾ�Ѿ�������0��ʾδ����
*********************************************************************************************************
*/
uint8_t bsp_IsLedOn(uint8_t _no)
{
	if (_no == 1)
	{
		if ((GPIO_PORT_LED1->ODR & GPIO_PIN_LED1) == 1)
		{
			return 1;
		}
		return 0;
	}
	if (_no == 2)
	{
		if ((GPIO_PORT_LED2->ODR & GPIO_PIN_LED2) == 1)
		{
			return 1;
		}
		return 0;
	}
	if (_no == 3)
	{
		if ((GPIO_PORT_LED3->ODR & GPIO_PIN_LED3) == 1)
		{
			return 1;
		}
		return 0;
	}


	return 0;
}

/***************************** ���������� www.armfly.com (END OF FILE) *********************************/
