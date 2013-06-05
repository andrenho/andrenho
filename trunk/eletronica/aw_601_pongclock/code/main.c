//#define TEST

#include <stdint.h>
#ifndef TEST
#  include <avr/io.h>
#  include <avr/interrupt.h>
#  include <avr/wdt.h>

#  define F_CPU 8000000UL
#  include <util/delay.h>
#endif

// led display
static uint32_t leds[16] = { 0 };

#ifdef TEST
#  include "curses.c"
#endif

uint32_t font[] = {
	//A  B  C  D  E  F  G  H  I  J
	//|  |  |  |  |  |  |  |  |  |
	0b111111111110111111111101111111,
	0b101101100101100100100101010001,
	0b111111100101110110111111010001,
	0b101101100101100100101101010101,
	0b101111111111111100111101111111,
};

// function prototypes
static void init_ports();
static void set_xy(int x, int y, uint32_t v);
static void check_events();
static void draw_leds();

int main()
{
	init_ports();

	set_xy(2, 2, 1);

	while(1)
	{
		check_events();
		draw_leds();
	}

	return 0;
}


static void set_xy(int x, int y, uint32_t v)
{
	if(v == 0)
		leds[y] &= ~(1 << x);
	else
		leds[y] |= (1 << x);
}


#ifndef TEST
static void init_ports()
{
}


static void check_events()
{
}


static void draw_leds()
{
}
#endif
