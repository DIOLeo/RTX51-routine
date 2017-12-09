/*******************************
AUTHOR:DIOLeo
DATE:2017.12.09
VERSION:V1.0

�򵥵�LED��ʾ����
Simple LED display application
P0.0 - LED0
P0.1 - LED1
P0.2 - LED2
�����ʹ�õ������пƼ��Ŀ����壬��P0����һ�����߲���J12����
ʱ��ƬΪ10ms��������Ĵ�Conf_tny.A51����36��INT_CLOCK��ֵ��Ϊ����Ҫ�����ּ���.Ĭ��10000 = 10ms
INT_CLOCK is the definition of Hardware-Timer tick time in 8051 machine cycles.
The defult value is 10000 which means 10ms
If you want to change it,open Conf_tny.A51 and go to line 36
*******************************/
#include "userdefine.h"

//����ȫ�ֱ���,���㲨�η���ʱ�鿴
uint32 tick1 = 0;
uint32 tick2 = 0;
uint32 tick3 = 0;

void job0() _task_ 0		//����0
{
	P0 = 0;					//��ʼ���˿�
	os_create_task(1);		//��������1
	os_create_task(2);		//��������2
	os_create_task(3);		//��������3
	
	os_delete_task(0);		//ɾ������0(��Ϊ����0�����þ��ǳ�ʼ���Ϳ�����������,����RTX51��̱�׼ÿһ�����񶼱��������ѭ����������Ҫɾ�����������޷�����)
}

void job1() _task_ 1		//����1
{
	while(1)
	{
		os_wait2(K_TMO,50);		//�ȴ�50��ʱ��Ƭ,��ȴ�ʱ����50*INT_CLOCK=500ms
		P0_0 = P0_0 == 0?1:0;	//P0_0��ת
		tick1 = tick1==0?1:0;	//tick1��ת
	}
}

void job2() _task_ 2		//����2
{
	while(1)
	{
		os_wait2(K_TMO,100);	//�ȴ�100��ʱ��Ƭ,��ȴ�ʱ����50*INT_CLOCK=1s
		P0_1 = P0_1 == 0?1:0;	//P0_1��ת
		tick2 = tick2==0?1:0;	//tick2��ת
	}
}

void job3() _task_ 3		//����3
{
	while(1)
	{
		os_wait2(K_TMO,200);	//�ȴ�200��ʱ��Ƭ,��ȴ�ʱ����50*INT_CLOCK=2s
		P0_2 = P0_2 == 0?1:0;	//P0_2��ת
		tick3 = tick3==0?1:0;	//tick3��ת
	}
}