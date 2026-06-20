#include<lpc21xx.h>		// LPC21xx register definitions
#include "can_defines.h"	// CAN register and bit definitions
#include "leds.h"			// Indicator LED function declarations
#include "delay.h"			// Delay function declarations
#include "defines.h"		// Bit manipulation macros
#include "can.h"			// CAN communication function declarations

#define LEDS 23			// Starting bit position for LED connections

int main()
{

	CANF rxFrame;		// CAN receive frame structure

	LED_Init();			// Initialize indicator LEDs

	Init_CAN1();		// Initialize CAN1 peripheral

	while(1)
	{
		if(READBIT(C1GSR,RBS_BIT))	// Check if CAN receive buffer contains new data
		{
			CAN1_Rx(&rxFrame);		// Receive CAN frame
		}

		if(rxFrame.Data1=='L')		// Check for left indicator command
		{
			left_indicator();		// Blink left indicator LEDs
		}
		else if(rxFrame.Data1=='R')	// Check for right indicator command
		{
			right_indicator();		// Blink right indicator LEDs
		}
		else if(rxFrame.Data1==0)	// Check for indicator OFF command
		{
			indicator_off();		// Turn OFF all indicator LEDs
		}

	}
}