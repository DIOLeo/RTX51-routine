/*******************************
AUTHOR:DIOLeo
DATE:2017.12.09
VERSION:V1.0

简单的LED显示程序
Simple LED display application
P0.0 - LED0
P0.1 - LED1
P0.2 - LED2
如果您使用的是普中科技的开发板，将P0口用一个排线插在J12即可
时间片为10ms，如需更改打开Conf_tny.A51将第36行INT_CLOCK的值改为你想要的数字即可.默认10000 = 10ms
INT_CLOCK is the definition of Hardware-Timer tick time in 8051 machine cycles.
The defult value is 10000 which means 10ms
If you want to change it,open Conf_tny.A51 and go to line 36
*******************************/
#include "userdefine.h"

//三个全局变量,方便波形仿真时查看
uint32 tick1 = 0;
uint32 tick2 = 0;
uint32 tick3 = 0;

void job0() _task_ 0		//任务0
{
	P0 = 0;					//初始化端口
	os_create_task(1);		//开启任务1
	os_create_task(2);		//开启任务2
	os_create_task(3);		//开启任务3
	
	os_delete_task(0);		//删除任务0(因为任务0的作用就是初始化和开启各个任务,根据RTX51编程标准每一个任务都必须带有死循环，所以需要删除否则程序会无法运行)
}

void job1() _task_ 1		//任务1
{
	while(1)
	{
		os_wait2(K_TMO,50);		//等待50个时间片,其等待时间是50*INT_CLOCK=500ms
		P0_0 = P0_0 == 0?1:0;	//P0_0翻转
		tick1 = tick1==0?1:0;	//tick1翻转
	}
}

void job2() _task_ 2		//任务2
{
	while(1)
	{
		os_wait2(K_TMO,100);	//等待100个时间片,其等待时间是50*INT_CLOCK=1s
		P0_1 = P0_1 == 0?1:0;	//P0_1翻转
		tick2 = tick2==0?1:0;	//tick2翻转
	}
}

void job3() _task_ 3		//任务3
{
	while(1)
	{
		os_wait2(K_TMO,200);	//等待200个时间片,其等待时间是50*INT_CLOCK=2s
		P0_2 = P0_2 == 0?1:0;	//P0_2翻转
		tick3 = tick3==0?1:0;	//tick3翻转
	}
}