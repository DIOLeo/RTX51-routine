#include "lcd1602.h"

#define LCD_DB P0
#define LCD_RS P2_6
#define LCD_RW P2_5
#define LCD_E  P2_7

void lcd1602Init()
{
	lcd1602WriteCmd(0x38);  //开显示
	lcd1602WriteCmd(0x0c);  //开显示不显示光标
	lcd1602WriteCmd(0x06);  //写一个指针加1
	lcd1602WriteCmd(0x01);  //清屏
}

void lcd1602WriteCmd(uint8 dat)
{
	LCD_RS = 0;
	LCD_RW = 0;
	LCD_DB = dat;
	delay_100us(1);
	LCD_E = 1;
	delay_100us(5);
	LCD_E = 0;
}

void lcd1602WriteData(uint8 dat)
{
	LCD_RS = 1;
	LCD_RW = 0;
	LCD_DB = dat;
	delay_100us(1);
	LCD_E = 1;
	delay_100us(5);
	LCD_E = 0;
}

void lcd1602ShowChar(uint8 line,uint8 pos,uint8 cha)
{
	if(line == 1)
	{
		lcd1602WriteCmd(0x80+pos-1);
		lcd1602WriteData(cha);
	}else if(line == 2)
	{
		lcd1602WriteCmd(0xC0+pos-1);
		lcd1602WriteData(cha);
	}else return;
}

void lcd1602ShowString(uint8 line,uint8 *cha)
{
	uint8 i=0;
	if(line == 1)
	{
		lcd1602WriteCmd(0x80);
		while(cha[i]!='\0')		lcd1602WriteData(cha[i++]);
	}else if(line == 2)
	{
		lcd1602WriteCmd(0xc0);
		while(cha[i]!='\0')		lcd1602WriteData(cha[i++]);
	}else return;
}

void lcd1602Move(uint8 direction)
{
	if(direction == LCD_MOVE_RIGHT)		lcd1602WriteCmd(0x1c);
	else if(direction == LCD_MOVE_LEFT)	lcd1602WriteCmd(0x18);
}

void lcd1602Switch(uint8 st)
{
	if(LCD_ON == st)		lcd1602WriteCmd(0x0D);
	else if(LCD_OFF == st)	lcd1602WriteCmd(0x09);
}