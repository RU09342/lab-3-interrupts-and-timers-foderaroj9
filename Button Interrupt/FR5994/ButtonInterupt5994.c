#include <msp430.h>
/*
 *Joe Foderaro
 *Lab3: Button Interupt
 *FR5994
 */
#define BUTTON BIT5				
#define LED   BIT0				

void main(void) {
	WDTCTL = WDTPW | WDTHOLD;	            //stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;                   //Disable the GPIO power-on default high-z mode
	P1DIR |= LED;				            //set LED pin as output
	P5DIR &= ~BUTTON;			            //set button as input
	P5REN |= BUTTON;			            //Enable pull-resistor
	P5OUT |= BUTTON;		            	//Make pull-resistor a pull-up

	P5IES &= ~BUTTON;			            //Rising edge interrupt
	P5IE |= BUTTON;		 		            //Enable interrupt on BUTTON

	_bis_SR_register(LPM4_bits + GIE);      //Enter low power mode and enable interupt
}

#pragma vector=PORT1_VECTOR		
__interrupt void Port_5(void)
{
	P1OUT ^= LED;				            //Toggle LED
	P5IFG &= ~BUTTON;			            //Clear BUTTON interrupt flag
}