/*******************************
AUTHOR:DIOLeo
DATE:2017.12.12
VERSION:V1.0

基于DS1302的LCD1602显示时间程序
LCD1602 display time application based on DS1302
如果您使用的是普中科技的开发板，短接JP1302跳线帽并插上1602模块即可
时间片为10ms，如需更改打开Conf_tny.A51将第36行INT_CLOCK的值改为你想要的数字即可.默认10000 = 10ms
INT_CLOCK is the definition of Hardware-Timer tick time in 8051 machine cycles.
The defult value is 10000 which means 10ms
If you want to change it,open Conf_tny.A51 and go to line 36
*******************************/
#include "userdefine.h"

DS1302Type DS1302Str;

void job0() _task_ 0		//任务0
{
	DS1302Str.display[2] = DS1302Str.display[5] = '-';	//将显示数组的连接符默认为'-'
	lcd1602Init();			//初始化1602
	ds1302Init();			//初始化1302
	os_create_task(1);		//开启任务1
	
	os_delete_task(0);		//删除任务0(因为任务0的作用就是初始化和开启各个任务,根据RTX51编程标准每一个任务都必须带有死循环，所以需要删除否则程序会无法运行)
}

void job1() _task_ 1		//任务1
{
	while(1)
	{
		DS1302DataProcess(DS1302Str.time,DS1302Str.display);	//1302接受当前时间到显示数组
		DS1302Display(DS1302Str.display);						//1302在1602上显示
	}
}

