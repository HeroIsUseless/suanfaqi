#include "MSP430.h"

void main(void)
{

    WDTCTL = WDTPW | WDTHOLD;   //�رտ��Ź���ʱ��

    P1DIR |= BIT0;
    P1OUT |= BIT0;

    P1DIR &= ~BIT3;                    // P1.3��Ϊ����
    P1REN |= BIT3;                     //����P1.3�ڲ�����������
    P1OUT |= BIT3;                     //����������Ϊ����
    P1IE  |= BIT3;                    // ����P1.3�ж�
    P1IES |= BIT3;                     // P1.3��Ϊ�½����ж�

    _enable_interrupts();              //��ͬ_EINT��ʹ�����ж�
    while(1){}
    return 0;
}

#pragma vector = PORT1_VECTOR
__interrupt void PORT1_ISR(void)
{
    _delay_cycles(10000);
    if((P1IN & BIT3) == 0){ // ��Ϊ�������½��أ�֮���ǵ͵�ƽ
        P1OUT ^= BIT0;
    }
    P1IFG=0;
}

