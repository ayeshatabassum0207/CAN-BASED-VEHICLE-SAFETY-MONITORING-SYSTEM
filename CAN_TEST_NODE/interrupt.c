//interrupt.c
#include <lpc21xx.h>
#include "interrupt_defines.h"
#include "types.h"
#include "interrupt.h"

void interrupt_initialization(void)
{	//cfg p0.1,p0.3 pin as EINT0,EINT1
PINSEL0&=((u32)~(3<<2)|(u32)~(3<<6));
 //UPDATE  bit 2 &3 ,bit 6 &7 for EINT0,EINT1
 PINSEL0|=EINT0_INPUT_PIN|EINT1_INPUT_PIN;

 //CFG VIC PERIPHERAL BLOCK
 //ALLOW EINT0 EINT1 AS IRQ BY DEFAULT IRQ ITSELF
 //VICIntSelect=0; //default
 //enable EINT0 EINT1 THROUGH CHANNEL
 VICIntEnable=1<<EINT0_VIC_CHNO|1<<EINT1_VIC_CHNO;

 //cfg eint0 as vIRQ WITH Highest priority (0)
 VICVectCntl0=(1<<5)|EINT0_VIC_CHNO;
 //Load eint0_isr address into LUT sfr
 VICVectAddr0=(u32)eint0_isr;

 //cfg eint0 as vIRQ WITH second Highest priority (1)
 VICVectCntl1=(1<<5)|EINT1_VIC_CHNO;				  
 //Load eint0_isr address into LUT sfr
 VICVectAddr1=(u32)eint1_isr;

 //cfg EINT0 EINT1 via external interrupts peripheral
 //enable EINT0 EINT1
 //EXTINT=0;//default
 //cfg as edge triggering input
 EXTMODE=((1<<1)|(1<<0));
 //CFG eint0 eint1 as falling edge trig
 EXTPOLAR=0;//BY DEFAULT
	

}

void eint0_isr(void) __irq

{
  
//clear EINT0 Status in Ext Int Peripheral

	EXTINT=1<<0;

	//clear EINT0 status in VIC peripheral

	VICVectAddr=0;

}


void eint1_isr(void) __irq

{
  	
	EXTINT=1<<1;

	//clear EINT1 status in VIC peripheral

	VICVectAddr=0;

}

