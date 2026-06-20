#include <lpc21xx.h>		// LPC21xx register definitions
#include "delay.h"			// Delay function declarations
#include "can.h"			// CAN communication function declarations
#include "defines.h"		// Bit manipulation macros

#define LEDS 23				// Starting bit position of indicator LEDs connected to Port 1

void LED_Init()
{
	IODIR1|=0XFF<<LEDS;		// Configure P1.23 to P1.30 as output pins

	IOPIN1|=0XFF<<LEDS;		// Set all indicator LEDs to OFF state
}

void indicator_off(void)
{
	IOSET1=0XFF<<LEDS;		// Turn OFF all indicator LEDs
}

void right_indicator(void)
{
	int i;					// Loop counter

	indicator_off();		// Ensure all LEDs are OFF before starting sequence

	delay_ms(100);			// Delay before indicator animation starts

	for(i=0;i<=7;i++)
	{
		IOCLR1=1<<(LEDS+i);	// Turn ON LEDs from left to right

		delay_ms(100);		// Delay between consecutive LEDs
	}
}

void left_indicator(void)
{
	int i;					// Loop counter

	indicator_off();		// Ensure all LEDs are OFF before starting sequence

	delay_ms(100);			// Delay before indicator animation starts

	for(i=7;i>=0;i--)
	{
		IOCLR1=1<<(LEDS+i);	// Turn ON LEDs from right to left

		delay_ms(100);		// Delay between consecutive LEDs
	}
}