#include<lpc21xx.h> 		// LPC21xx register definitions
#include "lcd.h"			// LCD function declarations
#include "interrupt_3.h"	// External interrupt function declarations
#include "ds.h"				// DS18B20 temperature sensor function declarations
#include "can.h"			// CAN communication function declarations
#include "can_defines.h"	// CAN register and bit definitions
#include "defines.h"		// General macro definitions
#include "fun.h"			// Buzzer and LCD indicator function declarations
#include "delay.h"			// Delay function declarations
#include "lcd_defines.h"	// LCD command and position macros

void interrupts_init(void);	// Function prototype for interrupt initialization

int l_flag=0,r_flag=0,mode=0;	// Global flags for left indicator, right indicator, and vehicle mode

char cgram[]={0x02,0x06,0x0e,0x1e,0x0e,0x06,0x02,0x00,0x10,0x18,0x1c,0x1e,0x1c,0x18,0x10,0x00};	// Custom LCD characters for left and right indicators

int main()
{

	int temp;	// Variable to store raw temperature data

	unsigned char tp,tpd;	// Variables to store integer and fractional parts of temperature

	//CAN_Frame
    CANF txFrame;	// CAN transmit frame structure
	CANF rxFrame;	// CAN receive frame structure

	LCD_Init();//LCD initialization
	Init_CAN1();	// Initialize CAN1 peripheral
	interrupts_init();	// Initialize external interrupts

	while(1)

	{
		Write_CMD_LCD(0x80);//selecting starting line and staring pos
		Write_CMD_LCD(0x0c);	// Turn ON LCD display and disable cursor
    	Write_str_LCD("Vehicle Safety Proj");	// Display project title on LCD

		Buildcgram(cgram,16);	// Load custom indicator symbols into LCD CGRAM

   		 //Write_CMD_LCD(0xC0);
		 if(ResetDS18b20()==0)	// Check presence of DS18B20 sensor
		 {
		 	temp=ReadTemp();  //READING TEMPERATURE FROM DS18B20 USING 1-WIRE PROTOCOL

			tp  = temp>>4;	  //GETTING INTEGER PART

			tpd=temp&0x08?0x35:0x30;//GETTING FRACTIONAL PART


			Write_CMD_LCD(0xC0);	// Move cursor to second line

 			Write_str_LCD("Engine Temp:");	// Display temperature label

			Write_int_LCD(tp);	// Display integer part of temperature

			Write_DAT_LCD('.');	// Display decimal point

			Write_DAT_LCD(tpd);	// Display fractional part

			Write_DAT_LCD(223);	// Display degree symbol

			Write_str_LCD(" C ");	// Display Celsius unit
		}
		else
		{
			Write_CMD_LCD(GOTO_LINE2_POS0+12);	// Move cursor to sensor status position

			Write_str_LCD("S.P    ");	// Display sensor presence error message
		}

		//cgram left and right
		Write_CMD_LCD(GOTO_LINE3_POS0);	// Move cursor to third line

		Write_str_LCD("INDICATOR:");	// Display indicator label

		//Buildcgram(cgramleft,16);

		Write_CMD_LCD(GOTO_LINE3_POS0+10);	// Move cursor to left indicator position

	   	Write_DAT_LCD(0);	// Display left indicator custom character

		Write_CMD_LCD(GOTO_LINE3_POS0+13);	// Move cursor to right indicator position

		Write_DAT_LCD(1);	// Display right indicator custom character


 		if((l_flag==1)&&(r_flag==0))	// Check if left indicator is active
		{
			txFrame.ID=1;	// Set CAN message ID

			txFrame.BFV.RTR=0;	// Configure as data frame

			txFrame.BFV.DLC=1;	// Set data length code

			txFrame.Data1='L';	// Send left indicator command

			//left indicator cgram blink
			blink_left_cgram();	// Blink left indicator symbol on LCD
		}
		else if(l_flag==2)	// Check if left indicator needs to be turned OFF
		{
			l_flag=0;	// Reset left indicator flag

			txFrame.ID=1;	// Set CAN message ID

			txFrame.BFV.RTR=0;	// Configure as data frame

			txFrame.BFV.DLC=1;	// Set data length code

			txFrame.Data1=0;	// Send indicator OFF command

		}

		if((r_flag==1)&&(l_flag==0))	// Check if right indicator is active
		{
			txFrame.ID=1;	// Set CAN message ID

			txFrame.BFV.RTR=0;	// Configure as data frame

			txFrame.BFV.DLC=1;	// Set data length code

			txFrame.Data1='R';	// Send right indicator command

			//blink_right_cgram();
			blink_right_cgram();	// Blink right indicator symbol on LCD
		}
		else if(r_flag==2)	// Check if right indicator needs to be turned OFF
		{
			r_flag=0;	// Reset right indicator flag

			txFrame.ID=1;	// Set CAN message ID

			txFrame.BFV.RTR=0;	// Configure as data frame

			txFrame.BFV.DLC=1;	// Set data length code

			txFrame.Data1=0;	// Send indicator OFF command

		}

		if(mode==1)	// Check if vehicle is in reverse mode
		{
			//recv reverse mode
			if(READBIT(C1GSR,RBS_BIT))	// Check if CAN receive buffer contains data
			{
				IOPIN0^=1<<20;	// Toggle debug LED pin

				CAN1_Rx(&rxFrame);	// Receive CAN frame from reverse alert node
			}

			Write_CMD_LCD(GOTO_LINE4_POS0+0);	// Move cursor to fourth line

			Write_str_LCD("Reverse mode ");	// Display reverse mode status

			Write_CMD_LCD(GOTO_LINE4_POS0+13);	// Move cursor to distance label position

			Write_str_LCD("Dist:");	// Display distance label

			Write_CMD_LCD(GOTO_LINE4_POS0+18);	// Move cursor to distance value position

			Write_str_LCD("  ");	// Clear previous distance value

			Write_CMD_LCD(GOTO_LINE4_POS0+18);	// Move cursor back to distance value position

			Write_int_LCD(rxFrame.Data2);	// Display received distance value

			if(rxFrame.Data1==1)	// Check if obstacle is detected
			{
				led_fun_on();	// Turn ON buzzer
			}
			else if(rxFrame.Data1==0)	// Check if no obstacle is detected
			{
				led_fun_off();	// Turn OFF buzzer
			}
		}
		else if(mode==0)	// Check if vehicle is in forward mode
		{

			Write_CMD_LCD(GOTO_LINE4_POS0);	// Move cursor to fourth line

			Write_str_LCD("In Forward mode     ");	// Display forward mode status
		}

		CAN1_Tx(txFrame);	// Transmit indicator status over CAN

	}
}