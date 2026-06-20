#include<lpc21xx.h>          // LPC21xx register definitions
#include "lcd.h"             // LCD function declarations
#include "lcd_defines.h"     // LCD command and position macros
#include "delay.h"           // Delay function declarations

#define BUZZER 17            // Buzzer connected to Port 1, Pin 17

void led_fun_on(void)
{
	IODIR1 |= 1 << BUZZER;   // Configure P1.17 as output
	IOCLR1 = 1 << BUZZER;    // Drive P1.17 LOW to turn ON the buzzer
}

void led_fun_off(void)
{
	//IODIR1 |= 1 << BUZZER; // Output configuration already done in led_fun_on()
	IOSET1 = 1 << BUZZER;    // Drive P1.17 HIGH to turn OFF the buzzer
}

void blink_left_cgram(void)
{
	Write_CMD_LCD(GOTO_LINE3_POS0 + 10); // Move cursor to line 3, position 10
	Write_DAT_LCD(0);                    // Display custom character stored at CGRAM location 0
	delay_ms(100);                       // Keep the symbol visible for 100 ms

	Write_CMD_LCD(GOTO_LINE3_POS0 + 10); // Move cursor back to the same position
	Write_DAT_LCD(' ');                  // Clear the displayed symbol
	delay_ms(100);                       // Keep the symbol hidden for 100 ms
}

void blink_right_cgram(void)
{
	Write_CMD_LCD(GOTO_LINE3_POS0 + 13); // Move cursor to line 3, position 13
	Write_DAT_LCD(1);                    // Display custom character stored at CGRAM location 1
	delay_ms(100);                       // Keep the symbol visible for 100 ms

	Write_CMD_LCD(GOTO_LINE3_POS0 + 13); // Move cursor back to the same position
	Write_DAT_LCD(' ');                  // Clear the displayed symbol
	delay_ms(100);                       // Keep the symbol hidden for 100 ms
}