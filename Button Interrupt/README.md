# Button Interupt
The code for this lab is not much different than the simple button blink in Lab 2 where we used polling to blink an LED with a 50% duty cycle. In this lab we use interupts to trigger the LED. This is much more efficient because the processor clock can actually be used for other things because it is not constantly checking if the button has been pushed.

# The following boards are used in this lab:
* MSP430G2553
* MSP430F5529
* MSP430FR2311
* MSP430FR5994
* MSP430FR6989

## Dependencies
The dependencies for this lab is the MSP430.h library that is included when you build a new project in code composer

## Outputs:
The LEDs and Buttons used for this are the following pins. 
G2553: P1.0 and P1.3
5529: P1.0 and P1.1
5594: P1.0 and P5.5
2311: P1.0 and P1.1
6989: P1.0 and P1.1

## Code Functionality
* The general code for every board is the same. The differences include pin numbers for the inputs and outputs, and for the FR boards, High impedance mode must be turned off.
