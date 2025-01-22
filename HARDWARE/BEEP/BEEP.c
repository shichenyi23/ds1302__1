#include "BEEP.h"

void BEEP_GPIO_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(BEEP_RCC, ENABLE);	 //ʹ�ܶ˿�ʱ��

	GPIO_InitStructure.GPIO_Pin = BEEP_PIN;	 //�����������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD; 		 //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//�ٶ�50MHz
	
	GPIO_Init(BEEP_GPIO_PORT, &GPIO_InitStructure);	 //��ʼ��GPIO
}

