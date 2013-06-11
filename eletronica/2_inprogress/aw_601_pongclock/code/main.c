#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>

#define F_CPU 8000000UL
#include <util/delay.h>

#define DUTY 1

int main()
{
	DDRB = 0xff;
	DDRD = 0xff;

	while(1)
	{
		int i=0;
		for(i=0; i<8; i++)
		{
			PORTB |= (1<<PORTB0); // DATA
			PORTB |= (1<<PORTB4); // CLK
			PORTB &= ~(1<<PORTB4); // CLK
			PORTB &= ~(1<<PORTB0); // DATA
			PORTB |= (1<<PORTB4); // CLK
			PORTB &= ~(1<<PORTB4); // CLK
		}
		PORTB |= (1<<PORTB5); // STR
		PORTD |= (1<<PORTD5); // OE
	}

	/*
	while(1)
	{
		int i=0;
		for(i=0; i<4; i++)
		{
			PORTB |= (1<<PORTB1); // DATA
			PORTB |= (1<<PORTB2); // CLK
			PORTB &= ~(1<<PORTB2);
			PORTB &= ~(1<<PORTB1); // DATA
			PORTB |= (1<<PORTB2); // CLK
			PORTB &= ~(1<<PORTB2);
		}
		PORTB |= (1<<PORTB0); // STR
		PORTB |= (1<<PORTB3); // OE

		int j;
		for(j=0; j<15; j++)
		{
		for(i=0; i<4; i++)
		{
			PORTB &= ~(1<<PORTB1); // DATA
			PORTB |= (1<<PORTB2); // CLK
			PORTB &= ~(1<<PORTB2);
			PORTB |= (1<<PORTB1); // DATA
			PORTB |= (1<<PORTB2); // CLK
			PORTB &= ~(1<<PORTB2);
		}
		PORTB |= (1<<PORTB0); // STR
		PORTB |= (1<<PORTB3); // OE
		}
	}
	*/

	return 0;
}
