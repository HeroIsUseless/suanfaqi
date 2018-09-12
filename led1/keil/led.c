#include <reg52.h>
#define DATA P0
typedef unsigned char u8;
typedef unsigned int u16;
sbit seg_sel = P1^4;
sbit bit_sel = P1^5;
u8 code seg_tab[]= {0xc0, 0xf9, 0xa4, 0xb0, 
			0x99, 0x92, 0x82, 0xf8, 
			0x80, 0x90, 0x88, 0x83,
	 		0xc6, 0xa1, 0x86, 0x8e};
u8 code bit_tab[] = {0x80, 0x40, 0x20, 0x10, 
				0x08, 0x04, 0x02, 0x01};
void delay(u16 num)
{
	u16 x, y;
	for(x=num; x>0; x--)
		for(y=110; y>0; y--)
		{
			;//��ʱ1ms
		}
}
void display_led(u8 whitch_bit, u8 which_number)
{
	bit_sel = 1;
	DATA = bit_tab[whitch_bit];
	bit_sel = 0;
	delay(5);
	seg_sel = 1;
	DATA = seg_tab[which_number];
	seg_sel = 0;
	delay(5);
}

u8 key_scan(void)
{
	u8 temp, temp2;
	P2 = 0xf0;//��P2���0xf0
	temp = P2;
	if(temp != 0xf0)//��P2�����ֵ���������������ʱ
	{
		delay(5);
		temp = P2;
		if(temp != 0xf0)//˵���а�������
		{
			temp2 = temp & 0xf0;//��������λ
			P2 = 0x0f;//����P2���0x0f
			delay(1);
			temp = P2;//�ٶ���ֵ�ĵ���λ
			temp2 |= temp;//��������λ
			return temp2;
		}
		//while(P2 != 0x0f);
	}
}
u8 encode(u8 cod)
{
	u8 num;
	switch(cod)
	{
		case 0xee: num=0; break; 
		case 0xde: num=1; break; 
		case 0xbe: num=2; break; 
		case 0x7e: num=3; break;	
		case 0xed: num=4; break; 
		case 0xdd: num=5; break; 
		case 0xbd: num=6; break; 
		case 0x7d: num=7; break;  
		case 0xeb: num=8; break; 
		case 0xdb: num=9; break; 
		case 0xbb: num=10; break; 
		case 0x7b: num=11; break;	
		case 0xe7: num=12; break; 
		case 0xd7: num=13; break; 
		case 0xb7: num=14; break; 
		case 0x77: num=15; break;
	}
	return num;
}
void main(void)
{
	u8 num;
	u8 cod;
	P0 = 0xff;//�˿ڳ�ʼ����������ģʽ
	P1 = 0xff;
	seg_sel = 0;//LE��ֹ����
	bit_sel = 0;
	while(1)
	{
	cod = key_scan();
	num = encode(cod);
	 display_led(1,num);
	}
}