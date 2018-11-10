//现在假定还没有小数点，不用处理
#include <Keypad.h>
#include <LiquidCrystal.h>
#include <EEPROM.h>
#define ADDR(x) x*4  //取地址宏定义
#define INPUTROM 0
#define OUTPUTROM 1
//********************************************************//
  union data{float f; byte b[4];};//共用体类型定义，主要作用是把float转换成byte类型
  typedef struct{char ch[20]; int n;} string;//字符串类型定义
  
//********************************************************//
  string *lpstr;
  int li, lj;
  char lkey;
  float lInVal[10], lOutVal[10];
//********************************************************//
int pi = 1, po = 11;//输入区指针1-9共9个空间，输出区指针  //
const int pin = 0, pon = 10;//数据计数
int isIO = INPUTROM;//判断当前是哪一个空间，0代表输入空间，1代表输出空间，存储器define定义
//*******************************************************//
//********************************************************//
   LiquidCrystal lcd(13,12,11,10,9,8);//lcd显示屏定义   //
//********************************************************//
//********************************************************//
              const byte ROWS = 4;//四行                  //
              const byte COLS = 4;//四列                  //
              char keys[ROWS][COLS]={                     //
                  {'7','8','C','O'},                      //
                  {'4','5','U','D'},                      //
                  {'1','2','+','-'},                      //
                  {'.','0','A','R'}};                     //
  byte rowPins[ROWS]={4,5,6,7};//单片机上相连的行针脚     //
byte colPins[COLS]={A0,A1,A2,A3};//单片机上相连的行针脚   //
Keypad keypad = Keypad(makeKeymap(keys),rowPins,colPins,ROWS,COLS);//键盘定义
//********************************************************//
//除了main函数，其他函数不准调用全局变量
void myPrint(string *cpstr)//格式化的lcd输出方式
{
    int i;
    lcd.clear(); lcd.setCursor(0,0);
    if(isIO==INPUTROM) lcd.print("IO:I I:");
    else               lcd.print("IO:O I:");
    lcd.print(pi);lcd.print("/");lcd.print((int)E_Read(ADDR(pin)));
    lcd.print(" O:");lcd.print(po-10);lcd.print("/");lcd.print((int)E_Read(ADDR(pon)));
    lcd.setCursor(0,1);
    for(i=0; i<cpstr->n; i++){lcd.setCursor(i,1);lcd.print(cpstr->ch[i]);}  //
    if(cpstr != lpstr) free(cpstr);
    //字节泄露
}
float toFloat(string *cpstr){//字符串转浮点数
  int i, isDot = 0;float f = 0.0, dot = 1;
  for(i=0; i<cpstr->n; i++){
    if(cpstr->ch[i] == '.') isDot = 1;
    else{
      if(isDot){
        dot *= 0.1;
        f += (float)(cpstr->ch[i]-48)*dot;}
        else f = f*10 + (float)(cpstr->ch[i]-48);
    }
  }
  return f;
}
string* toString(float cf){//把浮点数转化为字符串，永远标准三位小数，小数整数分开算
  int i,tmp,num;
  string *pstr = (string*)malloc(sizeof(string));pstr->n = 0;
  num = (int)(cf*1000);//精度为1000位，除了0后三位一定是小数
  while(num != 0){ pstr->ch[pstr->n++] = num%10+48; num /= 10; } 
  for(i=0; i<pstr->n/2; i++)//转换一下，不然是倒置的
    {tmp = pstr->ch[i]; pstr->ch[i] = pstr->ch[pstr->n-1-i];  pstr->ch[pstr->n-1-i] = tmp; }
  if(pstr->n == 0){pstr->ch[0] = '0'; pstr->n = 1;}
  else{ if(pstr->n == 3){ for(i=0; i<3; i++) pstr->ch[pstr->n+1-i] = pstr->ch[pstr->n-i-1];
                          pstr->n += 2; pstr->ch[pstr->n-4] = '.'; pstr->ch[pstr->n-5] = '0';}
        else{ for(i=0; i<3; i++) pstr->ch[pstr->n-i] = pstr->ch[pstr->n-i-1]; 
              pstr->n += 1; pstr->ch[pstr->n-4] = '.';} }
  return pstr;
}
float E_Read(int cpos){
  int i; data d;
  for(i=0; i<4; i++) d.b[i] = EEPROM.read(cpos+i);
  return d.f;
}
void E_Write(int cpos, float cf){
  int i; data d;
  d.f = cf;
  for(i=0; i<4; i++) EEPROM.write(cpos+i, d.b[i]);
}

int AddResult(float cf){
  int addr;
  if((int)E_Read(ADDR(pon)) == 9) return 0;
  E_Write(ADDR(pon), (float)((int)E_Read(ADDR(pon))+1));
  addr = 10+(int)E_Read(ADDR(pon));
  E_Write(ADDR(addr), cf);
  return 1;
}
void onRunTime(float cInVal[],int cInValN){//用户使用,cInVal从1开始
  AddResult(cInVal[1]+cInVal[2]);
}
void setup() {
  lcd.begin(16,2); lcd.print("Algorithor--V1.0"); delay(1000); lcd.clear();//显示欢迎界面
  lcd.setCursor(0,1);lcd.cursor(); lcd.blink();//初始化
  lpstr = (string*)malloc(sizeof(string));
  lpstr->n = 0;
  myPrint(lpstr);}//一个全局变量的初始化

void loop() {
  lkey = keypad.getKey();//持续捕获按键
  if(lkey != NO_KEY){
    switch(lkey){
      //转换输入输出存储显示,Change
      case 'C':if(isIO==0) {isIO=1; myPrint(toString(E_Read(ADDR(po))));}
               else        {isIO=0; myPrint(toString(E_Read(ADDR(pi))));} 
               break;
      //打开关闭按钮,Open or close
      case 'O':break;
      //上翻一个数据，如果是最后一个数据，那么就不翻,Up
      case 'U':if(isIO==INPUTROM && pi <= (int)E_Read(ADDR(pin)))
                  {if(pi < 9){pi++; myPrint(toString(E_Read(ADDR(pi))));}}
               else if(isIO==OUTPUTROM && po < (int)E_Read(ADDR(pon))+10 && po > 0)
                  {if(po <19){po++; myPrint(toString(E_Read(ADDR(po))));}} 
               break;
      //下翻一个数据，如果是第一个数据，那么就不翻,Down
      case 'D':if(isIO==INPUTROM) {if(pi > 1){pi--; myPrint(toString(E_Read(ADDR(pi))));}}
               else               {if(po >11){po--; myPrint(toString(E_Read(ADDR(po))));}}
               break;
      //压入一个数据，把ch[]压进去，同时指针进一位，存储进一位，如果是最后一位，就原地覆盖，不再前进
      case '+':if(isIO == INPUTROM ){
                  E_Write(ADDR(pi),toFloat(lpstr));//写入
                  lpstr->n = 0;//清空字符串
                  if(pi < 9){pi++; E_Write(ADDR(pin), (float)((int)E_Read(pin)+1));}//没有到头，指针进一位，存储进一位
                  myPrint(toString(E_Read(ADDR(pi))));}
               break;
      //删除一个数据，循环过去
      case '-':if(isIO == INPUTROM && (int)E_Read(ADDR(pin))>0 && pi <= (int)E_Read(ADDR(pin))){
                 for(li=pi; li<(int)E_Read(ADDR(pin)); li++){for(lj=0; lj<4; lj++){EEPROM.write(ADDR(pi+li)+lj,EEPROM.read(ADDR(pi+li+1)+lj));}} //循环前移
                 E_Write(ADDR(pin), (float)((int)E_Read(ADDR(pin))-1));//计数减1
                 myPrint(toString(E_Read(pi)));} //返回显示
               break;
      //全部清零，包括输入输出，因为即使断电，也应该保存数据，但这个不用保存
      case 'A':isIO = INPUTROM;
                 for(li=0; li<20; li++) for(lj=0; lj<4; lj++) EEPROM.write(ADDR(pi+li)+lj, 0); //从头到尾全都写0
                 pi = 1; po = 11;
                 myPrint(toString(E_Read(ADDR(pi)))); 
               break;
      //开始执行函数
      case 'R':lInVal[0] = (int)E_Read(ADDR(pin));
              for(li=1; li<=(int)lInVal[0]; li++) lInVal[li] = E_Read(ADDR(li));
              E_Write(ADDR(pon), 0);
              onRunTime(lInVal, lInVal[0]);
              isIO = OUTPUTROM; po=11;
              myPrint(toString(E_Read(ADDR(po))));  
              break;
      //下面是数字输入组合部分，只是放入ch中，并显示到lcd中，有小数点控制
      default:  
                if(lkey == '.'){
                  lj = 0;//代表有没有小数点
                  for(li=0; li<lpstr->n; li++){
                    if(lpstr->ch[li] == '.')
                      lj = 1;
                  }
                  if(!lj) lpstr->ch[lpstr->n++] = lkey;                 
                }
                else lpstr->ch[lpstr->n++] = lkey;
                myPrint(lpstr);
                break;
    }//siwtch
    }//ifNotKey
}//loop
