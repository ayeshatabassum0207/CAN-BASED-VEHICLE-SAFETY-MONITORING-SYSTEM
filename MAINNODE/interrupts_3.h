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
void interrupts_init();