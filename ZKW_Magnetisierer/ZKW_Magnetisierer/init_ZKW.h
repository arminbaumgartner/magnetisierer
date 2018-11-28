void init_timer(void)
{
	TCCR0B = TCCR0B | (1<<CS00);		//Pre-scaler 1024 (8MHz/1024 = 128µs)
	TCCR0B = TCCR0B &~ (1<<CS01);
	TCCR0B = TCCR0B | (1<<CS02);
	
	
	
	TIMSK = TIMSK | (1<<OCIE0A);	//interrupt
	OCR0A = 156;
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
	MCUCR = MCUCR &~ (1<<ISC00);		//falling edge
	MCUCR = MCUCR | (1<<ISC01);
	
	GIMSK = GIMSK | (1<<INT0);		//Int0 Interrupt freischalten
}