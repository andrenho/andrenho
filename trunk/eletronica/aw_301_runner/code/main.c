#define F_CPU 4000000UL

#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/sleep.h>
#include <avr/wdt.h>
#include <util/delay.h>


#define PIEZO PORTD5
#define FOREVER 99


static void beep(int times)
{
	int i;
	for(i=0; i<times; i++)
	{
beep_again:
		PORTD |= (1<<PIEZO);
		_delay_ms(400);
		PORTD &= ~(1<<PIEZO);
		_delay_ms(300);
		if(times == FOREVER)
			goto beep_again;
	}
}


volatile uint8_t day, warmup;


static void read_controls()
{
	_delay_ms(500);

	// set piezo as output
	DDRD |= (1<<PIEZO);

	// set other ports as input and read them
	DDRB = 0b10000000;
	PORTB = 0b01111111; // set as pullup
	_delay_ms(100);
	day = ~(PINB) & 0b00111111;
	warmup = (PINB & 0b01000000 ? 0 : 1);

	// debug day
	DDRD |= (1<<PORTD4) | (1<<PORTD3) | (1<<PORTD2);
	DDRA |= (1<<PORTA0) | (1<<PORTA1);
	
	PORTD |= (day & 0x1) << PORTD4;
	PORTD |= ((day >> 1) & 0x1) << PORTD3;
	PORTD |= ((day >> 2) & 0x1) << PORTD2;
	PORTA |= ((day >> 3) & 0x1) << PORTA0;
	PORTA |= ((day >> 4) & 0x1) << PORTA1;

	if(day > 26)
		beep(FOREVER);
}


void warm_up()
{
	beep(3);

	int i;
	for(i=0; i<300; i++)
		_delay_ms(1000); // 5 min
}


void run(int time)
{
	beep(1);

	int i;
	for(i=0; i<time; i++)
	{
		_delay_ms(1000);
	}
}


void walk(int time)
{
	beep(2);

	int i;
	for(i=0; i<time; i++)
	{
		_delay_ms(1000);
	}
}


int main()
{
	read_controls();

	if(warmup)
		warm_up();
	
	switch(day)
	{
	/* W1 */
	case 0: case 1: case 2:
		run(60); walk(90); run(60); walk(90); run(60); walk(90);
		run(60); walk(90); run(60); walk(90); run(60); walk(90);
		run(60); walk(90); run(60);
		break;
	/* W2 */
	case 3: case 4: case 5:
  		run(90); walk(120); run(90); walk(120); run(90); walk(120); 
		run(90); walk(120); run(90); walk(120); run(90);
		break;
	/* W3 */
	case 6: case 7: case 8:
  		run(90); walk(90); run(180); walk(180); run(90); walk(90); 
		run(180);
		break;
	/* W4 */
	case 9: case 10: case 11:
  		run(180); walk(90); run(300); walk(150); run(180); walk(90);
		run(300);
		break;
	/* W5 */
	case 12:
		run(300); walk(180); run(300); walk(180); run(300); break;
	case 13:
		run(480); walk(300); run(480); break;
	case 14:
		run(1200); break;
	/* W6 */
	case 15:
		run(300); walk(180); run(480); walk(180); run(300); break;
	case 16:
		run(600); walk(180); run(600); break;
	case 17:
		run(1350); break;
	/* W7 */
	case 18: case 19: case 20:
		run(1500); break;
	/* W8 */
	case 21: case 22: case 23:
		run(1680); break;
	/* W9 */
	case 24: case 25: case 26:
		run(1800); break;

	default:
		beep(FOREVER);
	}

	warm_up();
	beep(FOREVER);

	return 0;
}
