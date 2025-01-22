#include "stm32f10x.h"                  // Device header
#include "delay.h"
#include "MatrixKey.h"
uint8_t MatrixKey_determine(void);

void MatrixKey_Init()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
		
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	
}

uint8_t MatrixKey_GetValue()
{
	uint8_t Key;
	
	GPIO_ResetBits(GPIOA, GPIO_Pin_4);
	GPIO_SetBits(GPIOA, GPIO_Pin_5);
	GPIO_SetBits(GPIOA, GPIO_Pin_6);
	GPIO_SetBits(GPIOA, GPIO_Pin_7);

	Key =  MatrixKey_determine();
	
	GPIO_ResetBits(GPIOA, GPIO_Pin_5); 
	GPIO_SetBits(GPIOA, GPIO_Pin_4);
	GPIO_SetBits(GPIOA, GPIO_Pin_6);
	GPIO_SetBits(GPIOA, GPIO_Pin_7);
	
	if(MatrixKey_determine())
	{
		Key = MatrixKey_determine() + 4;
	}
	
	GPIO_ResetBits(GPIOA, GPIO_Pin_6);
	GPIO_SetBits(GPIOA, GPIO_Pin_4);
	GPIO_SetBits(GPIOA, GPIO_Pin_5);
	GPIO_SetBits(GPIOA, GPIO_Pin_7);
	

	if(MatrixKey_determine())
	{
		Key = MatrixKey_determine() + 8;
	}
	
	GPIO_ResetBits(GPIOA, GPIO_Pin_7);
	GPIO_SetBits(GPIOA, GPIO_Pin_4);
	GPIO_SetBits(GPIOA, GPIO_Pin_5);
	GPIO_SetBits(GPIOA, GPIO_Pin_6);
	
	
	if(MatrixKey_determine())
	{
		Key = MatrixKey_determine() + 12;
	}
	
	return Key;
}

uint8_t MatrixKey_determine()
{
	uint8_t Key = 0;
	if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == 0)
	{
		delay_ms(25);
		if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == 0){Key = 4;}
	}
	
	if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1) == 0)
	{
		delay_ms(25);
		if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1) == 0){Key = 3;}
	}
	
	if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_2) == 0)
	{
		delay_ms(25);
		if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_2) == 0){Key = 2;}
	}
	
	if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_3) == 0)
	{
		delay_ms(25);
		if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_3) == 0){Key = 1;}
	}
	return Key;
}
