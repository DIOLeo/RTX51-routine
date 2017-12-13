/*******************************
AUTHOR:DIOLeo
DATE:2017.12.12
VERSION:V1.0

����DS1302��LCD1602��ʾʱ�����
LCD1602 display time application based on DS1302
�����ʹ�õ������пƼ��Ŀ����壬�̽�JP1302����ñ������1602ģ�鼴��
ʱ��ƬΪ10ms��������Ĵ�Conf_tny.A51����36��INT_CLOCK��ֵ��Ϊ����Ҫ�����ּ���.Ĭ��10000 = 10ms
INT_CLOCK is the definition of Hardware-Timer tick time in 8051 machine cycles.
The defult value is 10000 which means 10ms
If you want to change it,open Conf_tny.A51 and go to line 36
*******************************/
#include "userdefine.h"

DS1302Type DS1302Str;

void job0() _task_ 0		//����0
{
	DS1302Str.display[2] = DS1302Str.display[5] = '-';	//����ʾ��������ӷ�Ĭ��Ϊ'-'
	lcd1602Init();			//��ʼ��1602
	ds1302Init();			//��ʼ��1302
	os_create_task(1);		//��������1
	
	os_delete_task(0);		//ɾ������0(��Ϊ����0�����þ��ǳ�ʼ���Ϳ�����������,����RTX51��̱�׼ÿһ�����񶼱��������ѭ����������Ҫɾ�����������޷�����)
}

void job1() _task_ 1		//����1
{
	while(1)
	{
		DS1302DataProcess(DS1302Str.time,DS1302Str.display);	//1302���ܵ�ǰʱ�䵽��ʾ����
		DS1302Display(DS1302Str.display);						//1302��1602����ʾ
	}
}

