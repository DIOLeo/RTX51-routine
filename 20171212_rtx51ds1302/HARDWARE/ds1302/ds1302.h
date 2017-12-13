#ifndef __DS1302_H
#define __DS1302_H

#include "usermacro.h"
#include "intrins.h"
#include "at89x51.h"
#include "lcd1602.h"

#define DS1302_DSIO P3_4
#define DS1302_CE   P3_5
#define DS1302_CLK  P3_6

void ds1302Init();
void ds1302ReadTime(uint8 *p);
void DS1302DataProcess(uint8 *time,uint8 *disp);
void DS1302Display(uint8 *p);
void ds1302Write(uint8 addr,uint8 dat);
uint8 ds1302Read(uint8 addr);

typedef struct
{
	uint8 time[8];
	uint8 display[8];
}DS1302Type;

#endif