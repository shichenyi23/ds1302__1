#include "stm32f10x.h"                  // Device header
#include "delay.h"
#include  "LCD1602v1.h"

void GPIO_OUT_config(void)
{
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitTypeDef GPIOB_InitStruct;
	GPIOB_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIOB_InitStruct.GPIO_Pin  = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10
	|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
	GPIOB_InitStruct.GPIO_Speed =GPIO_Speed_50MHz ;
	GPIO_Init(GPIOB,&GPIOB_InitStruct);
	
}

                        

void LCD1602_Write_CMD(uint16_t CMD)
{
	CMD=CMD<<8;
	
	LCD_RS_Clr();
	LCD_RW_Clr();
	LCD_EN_Set();
	delay_ms(50);
	GPIO_Write(GPIOB,(GPIO_ReadOutputData(GPIOB)&0x00ff)|CMD);
	delay_ms(5);
	LCD_EN_Clr();
}
void LCD_Init(void)
{
GPIO_OUT_config();
	LCD1602_Write_CMD(0x38);
	delay_ms(5);
	LCD1602_Write_CMD(0x0C);
	delay_ms(5);
LCD1602_Write_CMD(0x06);
	delay_ms(5);
LCD1602_Write_CMD(0x01);
	delay_ms(5);
	
	
}
void LCD1602_Write_Data(unsigned char data)
{
	uint16_t d=(uint16_t)data;
	d=d<<8;
	
	LCD_RS_Set();
	LCD_RW_Clr();
	LCD_EN_Set();
	delay_ms(5);
GPIO_Write(GPIOB,(GPIO_ReadOutputData(GPIOB)&0x00ff)|d);
	delay_ms(5);
	LCD_EN_Clr();


}
void LCD1602_ClearScreen(void)
{
	LCD1602_Write_CMD( 0x01 );
}


void LCD1602_Set_Cursor(uint8_t x,uint8_t y)
{
uint8_t addr;
	if ( y == 0 )
		addr = 0x00 + x;
	else
		addr = 0x40 + x;
	LCD1602_Write_CMD( addr | 0x80 );

}
void LCD_Show_String(uint8_t x,uint8_t y,unsigned char *string)

{
LCD1602_Set_Cursor( y, x );
	while ( *string != '\0' )
	{
		LCD1602_Write_Data( *string++ );
	}
}
int LCD_POW(uint8_t x,uint8_t y)
{
unsigned char i;
	int result=1;
	for(i=0;i<y;i++){
	result*=x;
	}
	return result;
}
void LCD_ShowNum(unsigned char line,unsigned char coulmn,unsigned int num,uint8_t length)
{
unsigned char i;
	LCD1602_Set_Cursor( coulmn, line );
	for(i=length;i>0;i--){
	LCD1602_Write_Data( num/LCD_POW(10,i-1)%10+'0' );
	}
}

void LCD_ShowChar(unsigned char line,unsigned char coulmn,unsigned char c)

{
LCD1602_Set_Cursor( coulmn, line );
	LCD1602_Write_Data(c);
}

