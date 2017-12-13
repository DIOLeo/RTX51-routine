#ifndef _LCD1602_H
#define _LCD1602_H

#include "at89x51.h"
#include "intrins.h"
#include "delay.h"
#include "usermacro.h"

#define LCD_MOVE_RIGHT 1
#define LCD_MOVE_LEFT 0
#define LCD_ON 1
#define LCD_OFF 0

void lcd1602Init();
void lcd1602WriteCmd(uint8 dat);
void lcd1602WriteData(uint8 dat);
void lcd1602ShowChar(uint8 line,uint8 pos,uint8 cha);
void lcd1602ShowString(uint8 line,uint8 *cha);
void lcd1602Move(uint8 direction);
void lcd1602Switch(uint8 st);

#endif