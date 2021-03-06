/*
 * zkw_magnetisierer

 *
 * Created: 23.11.2018 11:21:59
 * Author : armin
 */ 

#define F_CPU 8000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "init_ZKW.h"
#include "interupt_ZKW.h"


int main(void)
{
	
	CLKPR = 0x80;						//Clock prescaler 16MHz
	CLKPR = 0x00;
	
//	DDRB = DDRB | (1<<DDB0);		//Debug
	DDRB = DDRB | (1<<DDB1);		//MOSFET
	
	DDRB = DDRB &~ (1<<DDB5);		//ADC
	
	
	DDRB = DDRB &~ (1<<DDB2);		//int0
	PORTB = PORTB | (1<<PB2);		//pullup
	
	DDRB = DDRB | (1<<DDB4);		//Debug LED
	PORTB = PORTB &~ (1<<PB4);
	
	
	
	
	//init_timer();
	init_adc();
	init_ext_interrupt();
	
	
	sei();
    
    while (1) 
    {
    }
}

