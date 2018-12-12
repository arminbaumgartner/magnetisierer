/*
Include datei 


*/

#define MOSFETTIME 10
#define V_CAP 30
#define WARTEZEIT 3

#define MOSFET_EIN PORTB = PORTB | (1<<PB1)
#define MOSFET_AUS PORTB = PORTB &~ (1<<PB1)

char volatile taster_ein = 0;

char volatile adc_high;
char volatile adc_low;

char volatile sleep_flag = 0;


void init_timer(void);
void init_adc(void);
void init_ext_interrupt(void);
void init_sleep_mode (void);
void sleep_on (void);


void mosfet_schalten(void);
void led_on (void);
