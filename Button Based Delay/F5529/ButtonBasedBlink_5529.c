/*
 *Joe Foderaro
 *Lab3: Button Based Delay
 *FR5529
 */

#include <msp430.h>

int PushedButton;

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;           //Stop watchdog timer
    P1SEL &= ~BIT0;                     //select GPIO
    P1DIR |= BIT0;                      //set LED at Port 1.0 as output

    P1DIR &= ~(BIT1);                   //set Button at Port 1.1 as input
    P1REN |= BIT1;                      //enable pull-up resistor on
    P1OUT |= BIT1;


    P1IE |= BIT1;                       //enable interrupt
    P1IES |= BIT1;                      //set as falling edge
    P1IFG &= ~(BIT1);                   //clear interrupt flag

    TA0CTL = TASSEL_1 + MC_1 + ID_1;    //Set up Timer A, Count up, and divider 2.
    TA0CCTL0 = 0x10;                    //Set up compare mode for CCTL
    TA0CCR0 = 10000;                    

    __enable_interrupt();               //enable interrupt
    _BIS_SR(LPM4_bits + GIE);           //Enter Low Power Mode 4
}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A0(void)
{

    P1OUT ^= 0x01;                      //Toggle LED

}

#pragma vector=PORT1_VECTOR
__interrupt void PORT_1(void)
{
    //Debouncing
    P1IE &= ~BIT1;
    __delay_cycles(1);

    if (PushedButton == 0)              //Falling-edge of button
    {
        TA1CTL = TASSEL_1+ MC_2;        //Selecting Timer A and Count Up indefinitely
        TA1CCR0 = 0xFFFF;               //Initialize value of TA1CCR0
        TA1CCTL0 = CAP;                 //Capture mode
        PushedButton = 1;
        TA0CCR0 = 1;                    //Reset CCR0

    }
    else if (PushedButton == 1)         //Rising-edge of a button
    {
        TA1CTL = MC_0;                  //Stop Counting
        TA0CCR0 = TA1R;                 //Assgin new value for CCR0
        if (TA0CCR0 > 100000)           //Set Fastest Rate
            TA0CCR0 = 0xFFFF;
        if (TA0CCR0 < 500)              //Set Slowest Rate
            TA0CCR0 = 500;
        TA1CTL = TACLR;                 //Clear Timer A1
        PushedButton = 0;
    }

    P1IES ^= BIT1;                      //toggle to set as rising edge
    P1IE |= BIT1;                       // Enable interrupt
    P1IFG &= ~(BIT1);                  
}