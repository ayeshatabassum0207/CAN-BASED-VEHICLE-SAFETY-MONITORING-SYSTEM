#include<lpc21xx.h>
#include "lcd.h"
#include "lcd_defines.h"
#include "delay.h"
int main()
{
	LCD_Init();
	Write_CMD_LCD(0X01);
	Write_DAT_LCD('A');
	Write_CMD_LCD(0xc0);
	Write_str_LCD("Hey");
	Write_CMD_LCD(0X94);
	Write_int_LCD(20);
	while(1);

}