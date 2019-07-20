#include "MSP430.h"

void main(void)
{

    WDTCTL = WDTPW | WDTHOLD;   //关闭看门狗定时器

    P1DIR |= BIT0;
    P1OUT |= BIT0;

    P1DIR &= ~BIT3;                    // P1.3设为输入
    P1REN |= BIT3;                     // 启用P1.3内部上下拉电阻
    P1OUT |= BIT3;                     // 将电阻设置为上拉
    P1IE  |= BIT3;                     // 允许P1.3中断
    P1IES |= BIT3;                     // P1.3设为下降沿中断

    _enable_interrupts();              // 等同_EINT，使能总中断
    while(1){}
    return 0;
}

#pragma vector = PORT1_VECTOR
__interrupt void PORT1_ISR(void)
{
    _delay_cycles(1000000);
    if((P1IN & BIT3) == 0){
        P1OUT ^= BIT0;
    }
    P1IFG=0;
}

