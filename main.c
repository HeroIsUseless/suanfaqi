//���ݶ�����
#include <reg52.h>
#define DATA P0
typedef unsigned int u16;
typedef unsigned char u8;
float ib[100] = {0.0}; //���뻺��
char ch[100] = {0};//��ʱ�ַ���
int cn = 0;//ch�ַ����ü�������
int isDot = 0;//�Ƿ���С����
int in = 0;
int ipos = 0;//��������ǰλ��
float ob[100] = {0.0}; //������棬������ű�����������ǿɶ�����д��
int on = 0;
int npos = 0;//�������ǰλ��
int isI;//���������ǲ��Ǵ������뻺�棬1�����ǣ�0������
extern void key_onRunKeyDown(float ib[100], int in, float ob[100])



//ͨ�ú�����
void delay(u16 num)//��ʱ����
{
}
//lcd������			  
void lcd_init(void)//��ʼ������
{
}
void lcd_cmd(u8 cmd)//ָ����ƺ���
{
}
void lcd_print(int type, u8 pos)//д�����ݺ���
{//���ض�λ��д��һ����������ĸ
}

//���̺�����
u8 key_scan(void)//������غ���
{//�������õ�����
	return 0;
}
u8 encode(u8 cod)//���뺯��
{
	return 0;
}
//�洢����
void eeprom_init()
{
}
void eeprom_write(int type, int pos, float value) //1�������룬0�������
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
	//��ʼ�������뻺������ÿ������������ʼ��Ϊ0���뻺���Ǵ�1��ʼ�ģ���Ȼ0Ҳ��
	while(1)
	{
		cod = key_scan();
		switch(cod)
		{
			case 0-9:	 //��û��д��ȥ֮ǰ��һֱ��һ���ַ������飬д��ȥ֮��Ž��м���
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
			case onOrOff://���Ӧ���ǵ�·������
				init();
				break;
		}

	}
	return 0;
}




