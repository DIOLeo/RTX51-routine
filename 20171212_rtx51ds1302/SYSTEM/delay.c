//////////////////////////////////////////
//2017-10-29
//Version:2.0
//Author:DIO
//////////////////////////////////////////
#include "delay.h"

void delay_ms(unsigned int t)
{
    unsigned char a,b,c;
	while(t--)
	{
    for(c=1;c>0;c--)
        for(b=142;b>0;b--)
            for(a=2;a>0;a--);
	}
}

void delay_100us(unsigned int t)
{
	unsigned char a,b;
	while(t--)
	{		
		for(b=1;b>0;b--)
        for(a=47;a>0;a--);
	}
}
