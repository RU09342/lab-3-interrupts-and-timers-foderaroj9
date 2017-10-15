#include <msp430.h>
/*
 *Joe Foderaro
 *Lab3: Button Interupt
 *FR6989
 */
#define BUTTON BIT1				
#define LED   BIT0				

void main(void) {
	WDTCTL = WDTPW | WDTHOLD;	            //stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;                   //Disable the GPIO power-on default high-z mode
	P1DIR |= LED;				            //set LED pin as output
	P1DIR &= ~BUTTON;			            //set button as input
	P1REN |= BUTTON;			            //Enable pull-resistor
	P1OUT |= BUTTON;		            	//Make pull-resistor a pull-up

	P1IES &= ~BUTTON;			            //Rising edge interrupt
	P1IE |= BUTTON;		 		            //Enable interrupt on BUTTON

	_bis_SR_register(LPM4_bits + GIE);      //Enter low power mode and enable interupt
}

#pragma vector=PORT1_VECTOR		
__interrupt void Port_1(void)
{
	P1OUT ^= LED;				            //Toggle LED
	P1IFG &= ~BUTTON;			            //Clear BUTTON interrupt flag
}