#include "MSP430G2553.h"

void main( void )
{
  WDTCTL = WDTPW|WDTHOLD;

  //--配置时钟-----
  BCSCTL1=CALBC1_1MHZ;
  DCOCTL=CALDCO_1MHZ;

  P1DIR|=BIT0; // LED初始化
  TACTL = TASSEL_1|ID_0|MC_1|TAIE|TACLR; // 定时器0初始化，使用ACLK辅助时钟 不分频 增计数模式 允许中断 计数器清零

  //----设置TACCRx的值-----
  TACCR0=32767;     //时钟是32.768K,那么值设为32678-1
  TACCR1=10000;         //TACCR1和TACCR2要小于TACCR0,否则不会产生中断
  TACCR2=20000;
  TACCTL0 |= CCIE;      // TACCR0中断
  TACCTL1 |= CCIE;      // TACCR1中断
  TACCTL2 |= CCIE;      // TACCR2中断

  _EINT();              // 总中断使能
  LPM3;                 // 进入低功耗模式，就不会一直while了
}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer0_A0(void)    //TACCR0中断
{
  P1OUT^=BIT0;    //LED反转
}

#pragma vector=TIMER0_A1_VECTOR
__interrupt void Timer0_A1(void)    //TACCR1中断,TACCR2中断和TA0溢出中断共用一个中断向量
{
//  switch(TAIV)
//  {
//  case 2:                           //TACCR1中断
//    P1OUT^=(1<<6);    //LED反转
//    break;
//  case 4:                           //TACCR2中断
//    P1OUT^=(1<<6);    //LED反转
//    break;
//  case 10:                          //TAIFG 溢出中断
//    P1OUT^=(1<<6);    //LED反转
//    break;
//  default:
//    break;
//  }
}
