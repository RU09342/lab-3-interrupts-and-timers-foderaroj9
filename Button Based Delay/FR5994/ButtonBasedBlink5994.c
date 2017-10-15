/*
 *Joe Foderaro
 *Lab3: Button Based Delay
 *FR5994
 */

#include <msp430.h>

int PushedButton;

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;           //Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;               //high-z removal   
    P1SEL &= ~BIT0;                     //select GPIO
    P1DIR |= BIT0;                      //set LED at Port 1.0 as output

    P5DIR &= ~(BIT5);                   //set Button at Port 1.1 as input
    P5REN |= BIT5;                      //enable pull-up resistor on
    P5OUT |= BIT5;


    P5IE |= BIT5;                       //enable interrupt
    P5IES |= BIT5;                      //set as falling edge
    P5IFG &= ~(BIT5);                   //clear interrupt flag

    TA0CTL = TASSEL_1 + MC_1 + ID_1;    //Set up Timer A, Count up, and divider 2.
    TA0CCTL0 = 0x10;                    //Set up compare mode for CCTL
    TA0CCR0 = 10000;                    

    __enable_interrupt();               //enable interrupt
    _BIS_SR(LPM4_bits + GIE);           //Enter Low Power Mode 4
}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A0(void)
{

    P5OUT ^= 0x01;                      //Toggle LED

}

#pragma vector=PORT1_VECTOR
__interrupt void PORT_5(void)
{
    //Debouncing
    P5IE &= ~BIT5;
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

    P5IES ^= BIT5;                      //toggle to set as rising edge
    P5IE |= BIT5;                       // Enable interrupt
    P5IFG &= ~(BIT5);                  
}