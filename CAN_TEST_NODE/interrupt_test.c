//eint0_eint1_irq_test.c

#include "types.h"
#include "delay.h"

#include <LPC21xx.h>


#define EINT0_INPUT_PIN 0x0000000C

#define EINT0_VIC_CHNO  14

//#define EINT0_STATUS_LED 16//@p1.16


#define EINT1_INPUT_PIN 0x000000C0

#define EINT1_VIC_CHNO  15

//#define EINT1_STATUS_LED 17//@p1.17
//EINT 2
#define EINT2_INPUT_PIN 0

#define EINT2_VIC_CHNO  0


void eint0_isr(void) __irq;

void eint1_isr(void) __irq;
void eint2_isr(void) __irq;


u32 gCount;


main()

{

	//cfg p0.1,p0.3 p0.7 pin as EINT0,EINT1,EINT2

  //input pins

	//clr bit pair 2&3 & bit pair 4&5, AND 14 15

	//w/o affecting other bits

	PINSEL0&=((u32)~3<<2)|((u32)~3<<6)|((u32)~3<<14);

	//update bit2&3,bit4&5 for EINT0,EINT1,EINT2

	//pin function

	PINSEL0|=EINT0_INPUT_PIN|EINT1_INPUT_PIN|EINT2_INPUT_PIN;

	

	//cfg VIC peripheral/block

	//allow EINT0,EINT1 as irq type

	//VICIntSelect=0; //default

	//enable EINT0,EINT1 through channel

	VICIntEnable=1<<EINT0_VIC_CHNO|

	             1<<EINT1_VIC_CHNO|1<<EINT2_VIC_CHNO;

	

	//Cfg EINT0 as v.irq with highest priority(0)

	VICVectCntl0=(1<<5)|EINT0_VIC_CHNO;

	//load eint0_isr address into LUT sfr

  VICVectAddr0=(u32 ) eint0_isr;


  //Cfg EINT1 as v.irq with next

	//highest priority(1)

	VICVectCntl1=(1<<5)|EINT1_VIC_CHNO;

	//load eint1_isr address into LUT sfr

  VICVectAddr1=(u32 ) eint1_isr;
  
	VICVectCntl2=(1<<5)|EINT2_VIC_CHNO;

	//load eint1_isr address into LUT sfr

  VICVectAddr2=(u32 ) eint2_isr;


  //Cfg EINT0,EINT1 via 

	//External Interrupts Peripheral	

	//Enable EINT0,EINT1

	//EXTINT=0;//default

	//Cfg EINT0,EINT1 as edge triggered interrupt

	EXTMODE=((1<<1)|(1<<0)|(1<<2));

	//cfg EINT0,EINT1 as falling edge triggered

	//EXTPOLAR=0;//default

	

}


void eint0_isr(void) __irq

{

	//toggle led as status that interrupt occurred

	//IOPIN1^=1<<EINT0_STATUS_LED;
	/*Write_CMD_LCD(0x01);
	Write_str_LCD("Interrupt 1");	*/

	//clear EINT0 Status in Ext Int Peripheral

	EXTINT=1<<0;

	//clear EINT0 status in VIC peripheral

	VICVectAddr=0;

}


void eint1_isr(void) __irq

{

	//toggle led as status that interrupt occurred

	//IOPIN1^=1<<EINT1_STATUS_LED;
	/*Write_CMD_LCD(0x01);
	Write_str_LCD("Interrupt 2"); */


	//clear EINT1 Status in Ext Int Peripheral

	EXTINT=1<<1;

	//clear EINT1 status in VIC peripheral

	VICVectAddr=0;

}
void eint2_isr(void) __irq

{

	//toggle led as status that interrupt occurred

	//IOPIN1^=1<<EINT1_STATUS_LED;
/*	Write_CMD_LCD(0x01);
	Write_str_LCD("Interrupt 3"); */


	//clear EINT1 Status in Ext Int Peripheral

	EXTINT=1<<2;

	//clear EINT1 status in VIC peripheral

	VICVectAddr=0;

}