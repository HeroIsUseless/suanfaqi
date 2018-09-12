//������
#include <reg52.h>
#define DATA P0
typedef unsigned int u16;
typedef unsigned char u8;
sbit rs = P2^1;
sbit rw = P1^5;
sbit en = P1^6;	   
//ͨ�ú�����
void delay(u16 num)
{
	u16 x, y;
	for(x=num; x>0; x--)
		for(y=110; y>0; y--){}
}
//lcd������
//���̺�����
//�洢����
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
	write_cmd(0x02);//��λ
	write_cmd(0x06);
	write_cmd(0x0c);
	write_cmd(0x38);//�������ã�8λ���ݿڣ�������ʾ
	write_cmd(0x01);//����
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
















