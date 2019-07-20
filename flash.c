#include "MSP430.h"

int main(){
    WDTCTL = WDTPW | WDTHOLD;
    P1DIR |= BIT0;
    for(;;){
        _delay_cycles(50000);
        P1OUT ^= BIT0;
    }
    return 0;
}
