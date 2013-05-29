#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>

#define F_CPU 16000000UL
#include <util/delay.h>

int main()
{
	DDRB = 1;
	while(1)
	{
		PORTB |= 1;
		_delay_us(10);
		PORTB &= ~1;
		_delay_us(2550);
	}

	return 0;
}
