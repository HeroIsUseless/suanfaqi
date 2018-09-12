//数据定义区
#include <reg52.h>
#define DATA P0
typedef unsigned int u16;
typedef unsigned char u8;
float ib[100] = {0.0}; //输入缓存
char ch[100] = {0};//临时字符串
int cn = 0;//ch字符串用计数变量
int isDot = 0;//是否有小数点
int in = 0;
int ipos = 0;//输入区当前位置
float ob[100] = {0.0}; //输出缓存，在这个脚本里输出缓存是可读不可写的
int on = 0;
int npos = 0;//输出区当前位置
int isI;//代表现在是不是处于输入缓存，1代表是，0代表不是
extern void key_onRunKeyDown(float ib[100], int in, float ob[100])



//通用函数区
void delay(u16 num)//延时函数
{
}
//lcd函数区			  
void lcd_init(void)//初始化函数
{
}
void lcd_cmd(u8 cmd)//指令控制函数
{
}
void lcd_print(int type, u8 pos)//写入数据函数
{//在特定位置写入一个数或者字母
}

//键盘函数区
u8 key_scan(void)//按键监控函数
{//返回有用的数据
	return 0;
}
u8 encode(u8 cod)//编码函数
{
	return 0;
}
//存储器区
void eeprom_init()
{
}
void eeprom_write(int type, int pos, float value) //1代表输入，0代表输出
{
}
float eeprom_read(int type, int pos)
{
}


int main(void)
{
	lcd_init();
	key_init();
	eeprom_init();
	//初始化在输入缓存区，每个缓存区都初始化为0输入缓存是从1开始的，当然0也有
	while(1)
	{
		cod = key_scan();
		switch(cod)
		{
			case 0-9:	 //在没有写进去之前，一直是一个字符串数组，写进去之后才进行计算
				if(isI == 0) return;
				if(cod == 0) if(ch[0] == '0') return;
				ch[cn] = cod;
				cn++;
				break;
			case /:
				if(isI == 0) return;
				if(isDot == 1) return;
				ch[cn] = '/';
				cn++;
				break;
			case .:
				if(isI == 0) return;
				if(isDot == 1) return;
				ch[cn] = '.';
				cn++;
				break;
			case smod:
					isI != isI;
					lcd_init(isI);
				break;
			case m+:  
				if(isI == 0) return;
				eeprom_insert(1, ipos, chToFloat(ch, n));
				break;
			case m-:
				if(isI == 0) return;
				eeprom_delete(1, ipos);
				break;
			case up:
				if(isI == 0)
				{
					on++;
					if(on == 100) on=0;
					lcd_print(0, on);
				}
				else
				{
				   in++;
				   if(in == 100) in=0;
				   lcd_print(1, in);
				}
				break;
			case down:
				if(isI == 0)
				{
					on--;
					if(on == -1) on=99;
					lcd_print(0, on);
				}
				else
				{
				   in++;
				   if(in == -1) in=99;
				   lcd_print(1, in);
				}
				break;
			case run:
				onRunKeyDown();
				break;
			case onOrOff://这个应该是电路的事情
				init();
				break;
		}

	}
	return 0;
}




