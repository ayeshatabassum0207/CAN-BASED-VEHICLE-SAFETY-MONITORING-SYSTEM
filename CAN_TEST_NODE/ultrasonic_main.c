//****requires 5v in supply
#include<lpc21xx.h>

#include"lcd.h"

#include"defines.h"


unsigned int get_dis(void);

void INIT_Ultrasonic(void);

unsigned int dist_cal(void);

int main()

{

	unsigned int dist;


	INIT_Ultrasonic();

	T0PR=12000000/1000000-1;

	 LCD_Init();

	while(1)

	{
	Write_CMD_LCD(0x80);

 	Write_str_LCD("distance:");

	dist=dist_cal();

	Write_int_LCD(dist);

	delay_ms(1000);

	Write_CMD_LCD(0x01);

	}

}