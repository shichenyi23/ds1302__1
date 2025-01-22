#include "key.h"

//����ΪPA0-PA4.
//��������

void KEY_Init(void)
{
	
	GPIO_InitTypeDef GPIO_InitStructure;

 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//ʹ��GPIOAʱ��
	//GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);//�ر�jtag��ʹ��SWD��������SWDģʽ����
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4;//PA 0/1/2/3/4
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
 	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIO
	
} 

u8 KEY_Scan(void)
{
	if(!key_run)//run������
		{	
			while(key_run==0);//�ȴ������ɿ�
			delay_ms(5);//��ʱ����	
			return 1;
		}
	if(!key_shift)//shift������
		{	
			while(key_shift==0);//�ȴ������ɿ�
			delay_ms(5);//��ʱ����	
			return 2;
		}
	if(!key_beep)//beep������
		{	
			while(key_beep==0);//�ȴ������ɿ�
			delay_ms(5);//��ʱ����	
			return 3;
		}
	if(!key_up)//up������
		{	
			while(key_up==0);//�ȴ������ɿ�
			delay_ms(5);//��ʱ����	
			return 4;
		}
	if(!key_down)//down������
		{	
			while(key_down==0);//�ȴ������ɿ�
			delay_ms(5);//��ʱ����	
			return 5;
		}
		return 0;
}
