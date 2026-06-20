#include<lpc21xx.h>			// LPC21xx register definitions
#include "delay.h"			// Delay function declarations

#define trr_pin 18			// Trigger pin connected to P1.18
#define echo_pin 19			// Echo pin connected to P1.19

void INIT_Ultrasonic(void)
{
	IODIR1|=(1<<trr_pin);		// Configure trigger pin as output

	IODIR1&=~(1<<echo_pin);		// Configure echo pin as input
}

void send_pulse(void)
{
	IOSET1=1<<trr_pin;			// Set trigger pin HIGH

	delay_us(10);				// Generate 10 µs trigger pulse

	IOCLR1=1<<trr_pin;			// Set trigger pin LOW
}

unsigned int read_echo(void)
{
	unsigned duration=0;		// Variable to store echo pulse duration

	while(((IOPIN1>>echo_pin)&1)==0);	// Wait until echo pin becomes HIGH

	T0TCR=0X02;					// Reset Timer0

	T0TCR=0X01;					// Start Timer0

	while((IOPIN1>>echo_pin)&1);	// Wait until echo pin becomes LOW

	T0TCR=0X00;					// Stop Timer0

	duration=T0TC;				// Read timer count value

	return duration; 			// Return echo pulse duration in microseconds

	/*unsigned int duration = 0;
    int timeout = 1000000; // Safety exit

    while(((IOPIN0>>echo_pin)&1)==0 && timeout--); // Wait for High

    T0TCR=0x02; // Reset Timer
    T0TCR=0x01; // Start Timer
    
    timeout = 1000000;
    while(((IOPIN0>>echo_pin)&1) && timeout--); // Wait for Low
    
    T0TCR=0x00; // Stop Timer
    duration=T0TC;
    return duration;*/
}

unsigned int dist_cal(void)
{
	unsigned pulse;			// Variable to store echo pulse width

	float dis;					// Variable to store calculated distance

	send_pulse();				// Trigger ultrasonic sensor

	pulse=read_echo();			// Measure echo pulse duration

	dis=pulse/59.0;			// Convert pulse duration to distance in centimeters

	return dis;				// Return calculated distance

	/*unsigned int pulse;
    send_pulse();
    pulse = read_echo();
    return (pulse / 58);*/
}