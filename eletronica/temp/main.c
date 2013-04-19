#include <avr/io.h>
#include <avr/interrupt.h>
 
#define LED PD5

void delay_ms(uint8_t ms) {
	uint16_t delay_count = 1000000/17500;
	volatile uint16_t i;
	while(ms != 0) {
		for(i=0; i != delay_count; i++)
			ms--;
	}
}

int main(void)
{
	DDRB = _BV(3);
	for(;;) {
		PORTB = 8;
		delay_ms(100);
		PORTB = 0;
		delay_ms(100);
	}

	return 0;
}
