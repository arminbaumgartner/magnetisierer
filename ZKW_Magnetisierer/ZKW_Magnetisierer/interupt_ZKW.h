

#define MOSFETTIME 2000
#define V_CAP 10
#define ZEITDAUER 5

#define MOSFET_EIN PORTB = PORTB | (1<<PB4)
#define MOSFET_AUS PORTB = PORTB &~ (1<<PB4)


char adc_low;
char adc_high;

uint8_t overflow_counter = 0;
char schalten = 0;

void mosfet_schalten(void)
{
	MOSFET_EIN;
	
	_delay_ms(MOSFETTIME);
	
	MOSFET_AUS;
}

ISR(TIMER0_COMPA_vect)
{
	TCNT0=0;
	
	
	overflow_counter++;
	
	if(overflow_counter >= ZEITDAUER)
	{
		PORTB = PORTB ^ (1<<PB0);
		overflow_counter = 0;
		schalten = 1;
		
	}
}
ISR (ADC_vect)
{
	PORTB = PORTB ^ (1<<PB1);
	adc_low = ADCL;
	adc_high = ADCH;
	
	
	if(adc_high >= V_CAP)
	{
		PORTB = PORTB | (1<<PB3);		//LED ein
	}
	else
	{
		PORTB = PORTB &~ (1<<PB3);		//LED aus
	}
	
	ADCSRA = ADCSRA | (1<<ADSC);	//Wandlung starten
}
ISR(INT0_vect)
{
	if(adc_high >= V_CAP && schalten == 1)
	{
		mosfet_schalten();
		schalten = 0;
	}
	
}