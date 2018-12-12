ISR(TIMER0_COMPA_vect)
{
	TCNT0=0;
	
	PORTB = PORTB ^ (1<<PB0);
	
	overflow_counter++;

	
	if(overflow_counter == ZEITDAUER) //6s
	{
		
		sleep_on();
		
	}
	
	if(overflow_counter >= 250)
	{
		overflow_counter=250; //overflow
	}
	
}
ISR(INT0_vect)
{
	
	
	//sleep_disable();
	
	overflow_counter = 0;
	
	TCNT0 = 0;
	
	if(adc_high >= V_CAP)
	{
		mosfet_schalten();
		led_on();
	}
	
	
	//ADCSRA = ADCSRA | (1<<ADSC);	//Wandlung starten
}