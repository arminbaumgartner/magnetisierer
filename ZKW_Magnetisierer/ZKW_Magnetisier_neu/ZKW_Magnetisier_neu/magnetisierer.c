
void init_timer(void)
{
	TCCR0B = TCCR0B &~ (1<<CS00);		//Pre-scaler 256 (31250kHz/256 = 8ms)
	TCCR0B = TCCR0B &~ (1<<CS01);
	TCCR0B = TCCR0B | (1<<CS02);
	
	TIMSK = TIMSK | (1<<OCIE0A);	//interrupt
	OCR0A = 255;					//2s
}

void init_adc(void)
{
	ADMUX = ADMUX &~ (1<<REFS0);		//Vcc as referenz
	ADMUX = ADMUX &~ (1<<REFS1);

	ADMUX = ADMUX | (1<<ADLAR);			//Left adjusted
	
	ADMUX = ADMUX &~ (1<<MUX0);			//PB5 ADC0 single ended
	ADMUX = ADMUX &~ (1<<MUX1);
	ADMUX = ADMUX &~ (1<<MUX2);
	ADMUX = ADMUX &~ (1<<MUX3);
	
	ADCSRA = ADCSRA | (1<<ADEN);		//ADC enable
	
	ADCSRA = ADCSRA | (1<<ADIE);		//Interrupt enable
	
	ADCSRA = ADCSRA &~ (1<<ADPS0);		//ADC prescaler
	ADCSRA = ADCSRA | (1<<ADPS1);		//Teiler 64
	ADCSRA = ADCSRA | (1<<ADPS2);
	
	ADCSRA = ADCSRA | (1<<ADSC);		//Wandlung starten
	
}

void init_ext_interrupt(void)
{
	/*
	MCUCR = MCUCR &~ (1<<ISC00);		//falling edge
	MCUCR = MCUCR | (1<<ISC01);
	*/
	
	MCUCR = MCUCR &~ (1<<ISC00);		//falling edge
	MCUCR = MCUCR &~ (1<<ISC01);
	
	GIMSK = GIMSK | (1<<INT0);		//Int0 Interrupt freischalten
}

void init_sleep_mode (void)
{	
	set_sleep_mode(SLEEP_MODE_PWR_DOWN);
}


void mosfet_schalten(void)
{
	MOSFET_EIN;
	
	_delay_ms(MOSFETTIME);
	
	MOSFET_AUS;
}
void led_on (void)
{
	PORTB = PORTB | (1<<PB4);
	_delay_ms(1000);			//1s einschalten
}

ISR(INT0_vect)
{
	if(taster_ein >= 10)
	{
		if(adc_high >= V_CAP)
		{
			sleep_flag = 0;
			mosfet_schalten();
			led_on();
			taster_ein = 0;
		}	
	}
	else
	{
		PORTB = PORTB &~ (1<<PB4);
	}
		
}

ISR(ADC_vect)
{
	adc_low = ADCL;
	adc_high = ADCH;
	

	if (adc_high >= V_CAP)
	{
		PORTB = PORTB ^ (1<<PB4);	//LED toggln
	}
	else
	{
		PORTB = PORTB &~ (1<<PB4);
	}
	
	
	ADCSRA = ADCSRA | (1<<ADSC);	//Wandlung starten
}

ISR (TIMER0_COMPA_vect)
{
	TCNT0 = 0;
	
	sleep_flag++;
	
	if(sleep_flag >= 200)
	{
		sleep_flag=200;
	}
}