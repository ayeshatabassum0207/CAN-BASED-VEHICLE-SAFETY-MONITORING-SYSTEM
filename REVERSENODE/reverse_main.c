#include<lpc21xx.h>			// LPC21xx register definitions
#include "delay.h"			// Delay function declarations
#include "ultrasonic.h"		// Ultrasonic sensor function declarations
#include "can.h"			// CAN communication function declarations
#include "lcd.h"			// LCD function declarations

int main()
{
	unsigned int dist;		// Variable to store measured distance
	CANF txFrame;			// CAN transmit frame structure
	CANF rxFrame; 			// CAN receive frame structure

	Init_CAN1();			// Initialize CAN1 peripheral
	INIT_Ultrasonic();		// Initialize ultrasonic sensor

	T0PR=12000000/1000000-1;	// Configure Timer0 prescaler for 1 µs resolution

	LCD_Init();				// Initialize LCD

	while(1)
	{
		dist=dist_cal();	// Measure distance using ultrasonic sensor

		delay_ms(60);		// Delay for sensor stabilization and periodic transmission
							// ********************************* later comment and check

		//Write_int_LCD(dist);	// Display measured distance on LCD

		//delay_ms(1000);		// Delay for LCD update observation

		//Write_CMD_LCD(0x01);	// Clear LCD display

		//rxFrame.Data1;		// Placeholder for received CAN data access

		if(dist<20)			// Check if object is within alert threshold
		{
			txFrame.ID=2;			// Set CAN message identifier
			txFrame.BFV.RTR=0;		// Configure as data frame (not remote frame)
			txFrame.BFV.DLC=5;		// Set data length code

			txFrame.Data1=1;		// Alert status: object detected within threshold
			txFrame.Data2=dist;		// Send measured distance

			CAN1_Tx(txFrame);		// Transmit CAN frame
		}
		else
		{
			txFrame.ID=2;			// Set CAN message identifier
			txFrame.BFV.RTR=0;		// Configure as data frame (not remote frame)
			txFrame.BFV.DLC=5;		// Set data length code

			txFrame.Data1=0;		// Alert status: no nearby object detected
			txFrame.Data2=dist;		// Send measured distance

			CAN1_Tx(txFrame);		// Transmit CAN frame
		}
	}
}