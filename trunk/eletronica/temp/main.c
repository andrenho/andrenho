#define F_CPU 8000000UL

#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/sleep.h>
#include <avr/wdt.h>
#include <util/delay.h>

const int runs[] = {
  60, 90, 60, 90, 60, 90, 60, 90, 60, 90, 60, 90, 60, 90, 60, 90, 0, // W1D1
  60, 90, 60, 90, 60, 90, 60, 90, 60, 90, 60, 90, 60, 90, 60, 90, 0, // W1D2
  60, 90, 60, 90, 60, 90, 60, 90, 60, 90, 60, 90, 60, 90, 60, 90, 0, // W1D3
  90, 120, 90, 120, 90, 120, 90, 120, 90, 120, 90, 120, 0, // W2D1
  90, 120, 90, 120, 90, 120, 90, 120, 90, 120, 90, 120, 0, // W2D2
  90, 120, 90, 120, 90, 120, 90, 120, 90, 120, 90, 120, 0, // W2D3
  90, 90, 180, 180, 90, 90, 180, 180, 0, // W3D1
  90, 90, 180, 180, 90, 90, 180, 180, 0, // W3D2
  90, 90, 180, 180, 90, 90, 180, 180, 0, // W3D3
  180, 90, 300, 150, 180, 90, 300, 0, // W4D1
  180, 90, 300, 150, 180, 90, 300, 0, // W4D2
  180, 90, 300, 150, 180, 90, 300, 0, // W4D3
  300, 180, 300, 180, 300, 0, // W5D1
  480, 300, 480, 0,           // W5D2
  1200, 0,                    // W5D3
  300, 180, 480, 180, 300, 0, // W6D1
  600, 180, 600, 0,           // W6D2
  1350, 0,                    // W6D3
  1500, 0, // W7D1
  1500, 0, // W7D2
  1500, 0, // W7D3
  1680, 0, // W8D1
  1680, 0, // W8D2
  1680, 0, // W8D3
  1800, 0, // W9D1
  1800, 0, // W9D2
  1800, 0, // W9D3
  0
};
const int days[] = { 
    0,  17,  34, // W1
   51,  64,  77, // W2
   90,  99, 108, // W3
  117, 125, 133, // W4
  141, 147, 151, // W5
  153, 159, 163, // W6
  165, 167, 169, // W7
  171, 173, 175, // W8
  177, 179, 181, // W9
  0
};


#define PIEZO PORTD5
#define FOREVER 99
#define DEBUG 0

#if DEBUG
#  include "serial.c"
#endif
#include "wdt.c"

volatile uint8_t day = 0;
volatile uint8_t current = 0;
volatile uint16_t timer = 0;
volatile enum State { WARMUP, RUN, WALK, WARMOUT } state = WARMUP;


#if DEBUG
static char* state_str(enum State s)
{
	switch(s)
	{
		case WARMUP: return "WARMUP";
		case RUN: return "RUN";
		case WALK: return "WALK";
		case WARMOUT: return "WARMOUT";
	}
	return "INVALID";
}
#endif


static void beep(int times)
{
	int i;
	for(i=0; i<times; i++)
	{
beep_again:
#if DEBUG
	USART_printf("Beep! ");
#endif
		PORTD |= (1<<PIEZO);
		_delay_ms(400);
		PORTD &= ~(1<<PIEZO);
		_delay_ms(300);
		if(times == FOREVER)
			goto beep_again;
	}
#if DEBUG
	USART_printf("\n");
#endif
}


static void read_controls()
{
	// set piezo as output
	DDRD |= (1<<PIEZO);

	// set other ports as input and read them
	DDRB = 0b10000000;
	PORTB = 0b01111111; // set as pullup
	day = !(PINB & 0b00111111);
	if(day > 26)
		beep(FOREVER);
	state = (PINB & 0b01000000 ? WARMUP : RUN);

	// set variables (TODO)
	//state = WARMUP;
	//day = 0;

	// set variables
	current = days[day];
	if(state == WARMUP)
	{
		timer = 300;
		beep(3);
	}
	else
	{
		timer = runs[current];
		beep(2);
	}
#if DEBUG
	USART_printf("New state: %s\n", state_str(state));
	USART_printf("Timer new value: %d\n", timer);
#endif
}


static void step()
{
	if(timer == 0)
	{
		if(state == WARMOUT)
			beep(FOREVER); // never leaves from here

		current++;
		if(runs[current] != 0)
		{
			timer = runs[current];
			if(state == WARMUP || state == WALK) {
				state = RUN;
				beep(1);
			} else if(state == RUN) {
				state = WALK;
				beep(2);
			}
		}
		else
		{
			state = WARMOUT;
			timer = 300;
			beep(3);
		}
#if DEBUG
		USART_printf("New state: %s\n", state_str(state));
		USART_printf("Timer new value: %d|\n", timer);
#endif
	}
	else
	{
		--timer;
		/*
		PORTD |= (1<<PIEZO);
		_delay_ms(50);
		PORTD &= ~(1<<PIEZO);
		*/
#if DEBUG
		USART_printf("Timer: %d\n", timer);
#endif
	}
}


int main()
{
#if DEBUG
	USART_init();
	USART_printf("c%dk\n", 25);
#endif
	read_controls();
	//watchdog_init();
	
	for(;;) 
		//if(f_wdt == 1)
		{
		//	f_wdt = 0;
			step();
			_delay_ms(1000);
		//	system_sleep();
		}

	return 0;
}
