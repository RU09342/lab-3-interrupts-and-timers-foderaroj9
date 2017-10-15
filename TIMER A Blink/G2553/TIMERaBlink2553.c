#include <msp430.h> 
/*
 *Joe Foderaro
 *Lab3: Timer A Blink
 *G2553
 */

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;               // stop watchdog timer
  
    P1SEL = 0x00;                           //sets P1 to GPIO
    P1SEL2 = 0x00;                          //sets P1 to GPIO
    P1DIR = (BIT0 + BIT6);                  //sets LED at P1.0 and P1.6 as output

    __bis_SR_register(GIE);                 //global interupt enable

    TA0CCTL0 = CCIE;                        // CCR0 interrupt enabled
    TA0CCR0 = 60000;                        //register that timer will compare itself too
    TA0CTL = TASSEL_2 + MC_1 + TACLR;       // SMCLK 8MHz, Count up to CCR0, clear TAR

    for(;;){}
    return 0;
}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void TIMER0_A0_ISR(void){
            P1OUT ^= BIT0;                  //toggle LED
            P1OUT ^= BIT6;                  //toggle LED
}