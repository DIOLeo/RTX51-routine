#include "ds1302.h"

//---DS1302д��Ͷ�ȡʱ����ĵ�ַ����---//
//---���ʱ�������� ���λ��дλ;-------//
static uint8 code DS1302_READADDR[7]  = {0x81, 0x83, 0x85, 0x87, 0x89, 0x8b, 0x8d}; 
static uint8 code DS1302_WRITEADDR[7] = {0x80, 0x82, 0x84, 0x86, 0x88, 0x8a, 0x8c};
static uint8 code DS1302_TIMEINIT[7]  = {0, 0, 0x12, 0x07, 0x05, 0x06, 0x16};

void ds1302Init()
{
	uint8 n;
	ds1302Write(0x8E,0X00);		//��ֹд���������ǹر�д��������
	for (n=0; n<7; n++)			//д��7���ֽڵ�ʱ���źţ�����ʱ��������
	{
		ds1302Write(DS1302_WRITEADDR[n],DS1302_TIMEINIT[n]);
	}
	ds1302Write(0x8E,0x80);		//��д��������
}

void ds1302ReadTime(uint8 *p)
{
	uint8 n;
	uint8 *readaddr = DS1302_READADDR;
	for (n=0; n<7; n++)
	{
		*(p++) = ds1302Read(*(readaddr++));
	}
}

void DS1302DataProcess(uint8 *time,uint8 *disp) 	 
{
   	ds1302ReadTime(time);
	
	*disp = (*(time+2)>>4)+'0';
	*(disp+1) = (*(time+2)&0x0f)+'0';
	*(disp+3) = (*(time+1)>>4)+'0';
	*(disp+4) = (*(time+1)&0x0f)+'0';	
	*(disp+6) = (*time>>4)+'0';
	*(disp+7) = (*time&0x0f)+'0';
}

void DS1302Display(uint8 *p)
{
	uint8 i;
	for(i=0;i<8;i++)
	{
		lcd1602ShowChar(1,i+1,*(p++));
	}
}

void ds1302Write(uint8 addr,uint8 dat)
{
	uint8 n;

	DS1302_CLK = 0;//�Ƚ�DS1302_CLK�õ͵�ƽ��
	DS1302_CE = 1; //Ȼ��DS1302_CE(CE)�øߵ�ƽ��
	_nop_();

	for (n=0;n<8;n++)//��ʼ���Ͱ�λ��ַ����
	{
		DS1302_DSIO = addr & 0x01;//���ݴӵ�λ��ʼ����
		addr >>= 1;
		DS1302_CLK = 1;//������������ʱ��DS1302��ȡ����
		DS1302_CLK = 0;
	}
	for (n=0;n<8;n++)//д��8λ����
	{
		DS1302_DSIO = dat & 0x01;
		dat >>= 1;
		DS1302_CLK = 1;//������������ʱ��DS1302��ȡ����
		DS1302_CLK = 0;
	}	
		 
	DS1302_CE = 0;//�������ݽ���
	_nop_();
}

uint8 ds1302Read(uint8 addr)
{
	uint8 n,dat,dat1;

	DS1302_CLK = 0;//�Ƚ�DS1302_CLK�õ͵�ƽ��
	DS1302_CE = 1;//Ȼ��DS1302_CE(CE)�øߵ�ƽ��
	_nop_();

	for(n=0;n<8;n++)//��ʼ���Ͱ�λ��ַ����
	{
		DS1302_DSIO = addr & 0x01;//���ݴӵ�λ��ʼ����
		addr >>= 1;
		DS1302_CLK = 1;
		DS1302_CLK = 0;//DS1302�½���ʱ����������
	}
	_nop_();
	for(n=0;n<8;n++)//��ȡ8λ����
	{
		dat1 = DS1302_DSIO;//�����λ��ʼ����
		dat = (dat>>1) | (dat1<<7);
		DS1302_CLK = 1;
		DS1302_CLK = 0;//DS1302�½���ʱ����������
	}

	DS1302_CE = 0;
	_nop_();	//����ΪDS1302��λ���ȶ�ʱ��,����ġ�
	DS1302_CLK = 1;
	_nop_();
	DS1302_DSIO = 0;
	_nop_();
	DS1302_DSIO = 1;
	_nop_();
	return dat;	
}

