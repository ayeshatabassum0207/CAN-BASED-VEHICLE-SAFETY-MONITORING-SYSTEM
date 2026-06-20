#include <LPC21xx.h>		// LPC21xx register definitions

#include "delay.h"			// Delay function declarations

#include "lcd.h"			// LCD function declarations

#include "defines.h"		// Bit manipulation macros


#define LCD_DAT 23			// Starting bit position of LCD data pins connected to Port1

#define RS 8				// Register Select pin connected to P0.8

#define RW 10				// Read/Write pin connected to P0.10

#define EN 9				// Enable pin connected to P0.9

void Buildcgram(char *p,char nb)
{
	int i;								// Loop counter

	Write_CMD_LCD(0x40);				// Set CGRAM address to store custom characters

	for(i=0;i<=nb;i++)
	{
	 Write_DAT_LCD(p[i]);				// Write custom character data to CGRAM
	}

	Write_CMD_LCD(0x80);				// Return cursor to DDRAM starting address
}

void LCD_Init(void)

{

	WRITEBYTE(IODIR1,LCD_DAT,0xFF);		// Configure LCD data pins as output

	WRITEBIT(IODIR0,RS,1);				// Configure RS pin as output
					  
	WRITEBIT(IODIR0,RW,1);				// Configure RW pin as output

	WRITEBIT(IODIR0,EN,1);				// Configure EN pin as output

	delay_ms(16);						// Wait for LCD power stabilization

    Write_CMD_LCD(0x30);				// Initialization sequence step 1

    delay_ms(6);

	Write_CMD_LCD(0x30);				// Initialization sequence step 2

    delay_ms(1);

    Write_CMD_LCD(0x30);				// Initialization sequence step 3

    delay_ms(1);

    Write_CMD_LCD(0x38);//set 8-bit mode of operation with 2 lines
						// and 5X7 character font

	Write_CMD_LCD(0x10);//Turning OFF the display

	Write_CMD_LCD(0x01);//clearing the display

    Write_CMD_LCD(0x06);//Shifting the cursor to the right side
                        //after writing each byte onto the display

	Write_CMD_LCD(0x0E);//Enabling the display with blinking off

}


void Write_CMD_LCD(char cmd)

{

    WRITEBIT(IOCLR0,RS,1);				// Select command register

    Write_LCD(cmd);						// Send command to LCD

}


void Write_DAT_LCD(char dat)

{

	WRITEBIT(IOSET0,RS,1);				// Select data register

	Write_LCD(dat);						// Send data to LCD

}


void Write_LCD(char ch)

{

	WRITEBIT(IOCLR0,RW,1);				// Configure LCD for write operation

	WRITEBYTE(IOPIN1,LCD_DAT,ch);		// Place data/command on data bus

	WRITEBIT(IOSET0,EN,1);				// Generate enable pulse (EN HIGH)

	WRITEBIT(IOCLR0,EN,1);				// Complete enable pulse (EN LOW)

	delay_ms(2);						// Wait for LCD processing time

}


void Write_str_LCD(char *p)

{

	while(*p)

		Write_DAT_LCD(*p++);			// Display characters until null terminator is reached

}


void Write_int_LCD(signed int n)

{

	char a[10],i=0;						// Buffer to store digits temporarily

    if(n<0)

	{

		Write_DAT_LCD('-');			// Display negative sign

		n=-n;							// Convert to positive number

	}

	do

	{

		a[i++]=n%10+48;				// Convert digit to ASCII and store

		n=n/10;						// Remove last digit

	}while(n);

	for(;i>0;i--)

		Write_DAT_LCD(a[i-1]);		// Display digits in correct order

}


void Write_float_LCD(float f,char i)

//1st arg(f) is the float number to be displayed  on LCD

//2nd arg(i) is number digits to be displayed after the dot('.')

{

	unsigned long int n=f;			// Extract integer part

	Write_int_LCD(n);				// Display integer part

	Write_DAT_LCD('.');				// Display decimal point

	for(;i>0;i--)

	{

		f=f*10;						// Shift next decimal digit to integer position

		n=f;

		Write_DAT_LCD(n%10+48);		// Display fractional digit

	}

}