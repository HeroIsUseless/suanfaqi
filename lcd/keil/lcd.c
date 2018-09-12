//定义区
#include <reg52.h>
#define DATA P0
typedef unsigned int u16;
typedef unsigned char u8;
sbit rs = P2^1;
sbit rw = P1^5;
sbit en = P1^6;	   
//通用函数区
void delay(u16 num)
{
	u16 x, y;
	for(x=num; x>0; x--)
		for(y=110; y>0; y--){}
}
//lcd函数区
//键盘函数区
//存储器区
void write_cmd(u8 cmd)
{
	rs = 0;
	rw = 0;	 
	DATA = cmd;
	delay(5);
	en = 1;
	delay(5);
	en = 0;
}
void write_data(u8 dat)
{
	rs = 1;
	rw = 0;	 
	DATA = dat;
	delay(5);
	en = 1;
	delay(5);
	en = 0;
}			  
void lcd_init(void)
{
	write_cmd(0x02);//归位
	write_cmd(0x06);
	write_cmd(0x0c);
	write_cmd(0x38);//功能设置，8位数据口，两行显示
	write_cmd(0x01);//清屏
}


int main(void)
{
	rw = 0;
	rs = 0;
	lcd_init();
	write_cmd(0x80);
	write_data('1');
	while(1);
	return 0;
}
















