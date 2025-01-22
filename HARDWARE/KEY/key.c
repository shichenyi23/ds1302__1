#include "key.h"

//按键为PA0-PA4.
//按键上拉

void KEY_Init(void)
{
	
	GPIO_InitTypeDef GPIO_InitStructure;

 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//使能GPIOA时钟
	//GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);//关闭jtag，使能SWD，可以用SWD模式调试
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4;//PA 0/1/2/3/4
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
 	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIO
	
} 

u8 KEY_Scan(void)
{
	if(!key_run)//run键按下
		{	
			while(key_run==0);//等待按键松开
			delay_ms(5);//延时消抖	
			return 1;
		}
	if(!key_shift)//shift键按下
		{	
			while(key_shift==0);//等待按键松开
			delay_ms(5);//延时消抖	
			return 2;
		}
	if(!key_beep)//beep键按下
		{	
			while(key_beep==0);//等待按键松开
			delay_ms(5);//延时消抖	
			return 3;
		}
	if(!key_up)//up键按下
		{	
			while(key_up==0);//等待按键松开
			delay_ms(5);//延时消抖	
			return 4;
		}
	if(!key_down)//down键按下
		{	
			while(key_down==0);//等待按键松开
			delay_ms(5);//延时消抖	
			return 5;
		}
		return 0;
}
