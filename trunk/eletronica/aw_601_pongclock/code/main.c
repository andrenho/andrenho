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
		_delay_ms(1);
		int i=0;
		for(i=0; i<1024; i++)
		{
			PORTB &= ~1;
		}
		_delay_ms(15);
	}

	return 0;
}
