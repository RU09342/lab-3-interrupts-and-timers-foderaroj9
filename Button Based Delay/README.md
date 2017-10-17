# Button Based Delay
The code for this lab is written in C and is used to blink an LED at a rate determined by holding down a button for a certain amount of time. This is done using two interupts and a timer. The loop is used to check if the button flag is true and When the button is pressed, the timer counts up indefinitely. When the button is released, the timer stops and the value is stored and then used as the new blink time.
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
