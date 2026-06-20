//interrupt.h
#include "interrupt_defines.h"
void interrupt_initialization(void);
void eint0_isr(void) __irq;
void eint1_isr(void) __irq;
