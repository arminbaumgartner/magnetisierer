/*
 * ZKW_Magnetisier_neu.c
 *
 * Created: 07.12.2018 10:36:28
 * Author : armin
 */ 

#define F_CPU 31250UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <util/delay.h>
#include "magnetisierer.h"
#include "magnetisierer.c"



int main(void)
{
    
	CLKPR = 0x80;						//Clock prescaler 16MHz
	CLKPR = 0x08;		//31.250kHz
	//CLKPR = 0x00;		//8MHz
	
	DDRB = DDRB | (1<<DDB0);		//Debug
	DDRB = DDRB | (1<<DDB1);		//MOSFET
	
	DDRB = DDRB &~ (1<<DDB5);		//ADC
	
	
	DDRB = DDRB &~ (1<<DDB2);		//int0
	PORTB = PORTB | (1<<PB2);		//pullup
	
	DDRB = DDRB | (1<<DDB4);		//Debug LED
	PORTB = PORTB &~ (1<<PB4);
	
	
	init_ext_interrupt();
	init_adc();
	init_timer();
	
	init_sleep_mode();
	
	
	sei();
	
	sleep_mode();

    while (1) 
    {
		
		taster_ein++;
		
		if (taster_ein >= 200)
		{
			taster_ein = 200;
		}
		
		
		if (sleep_flag >= WARTEZEIT)
		{
			PORTB = PORTB &~ (1<<PB4);
			sleep_mode();
			sleep_flag = 0;
		}
		
	}
    
}

