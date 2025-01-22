#ifndef LCD1602_H__
#define LCD1602_H__
#define LCD_RS_Set()	GPIO_SetBits( GPIOB, GPIO_Pin_5 )
#define LCD_RS_Clr()	GPIO_ResetBits( GPIOB, GPIO_Pin_5 )

#define LCD_RW_Set()	GPIO_SetBits( GPIOB, GPIO_Pin_4 )
#define LCD_RW_Clr()	GPIO_ResetBits( GPIOB, GPIO_Pin_4 )

#define LCD_EN_Set()	GPIO_SetBits( GPIOB, GPIO_Pin_3 )
#define LCD_EN_Clr()	GPIO_ResetBits( GPIOB, GPIO_Pin_3 )
#define DATAOUT( x ) GPIO_Write( GPIOB, x )

void GPIO_OUT_config(void);
void LCD1602_Write_CMD(uint16_t CMD);
void LCD_Init(void);
void LCD1602_Write_Data(unsigned char data);
void LCD1602_ClearScreen(void);
void LCD1602_Set_Cursor(uint8_t x,uint8_t y);
void LCD_Show_String(uint8_t x,uint8_t y,unsigned char *string);
int LCD_POW(uint8_t x,uint8_t y);
void LCD_ShowNum(unsigned char line,unsigned char coulmn,unsigned int num,uint8_t length);
void LCD_ShowChar(unsigned char line,unsigned char coulmn,unsigned char c);

#endif
