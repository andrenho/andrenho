#define F_CPU 4000000UL

#include <stdbool.h>

#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

// global variables
volatile int16_t timer[3];
volatile bool beep[3];


static inline void initialize()
{
	// initialize variables
	int i;
	for(i=0; i<3; i++)
	{
		timer[i] = 0;
		beep[i] = false;
	}

	// initialize I/O ports
	DDRB = 0xff;		// 7-segment digits
	DDRD = 0b01000000;	// PD* = input, PD6 = digit
	PORTD = 0b00111111;     // set inputs as pullup

	// give time to ports adjust
	_delay_ms(100);

	// initialize general timer (for seconds)
	//   (((Input_Freq / Prescaler) / Target_Freq) - 1)
	//   (((4.000.000 / 256) / 1) - 1) = 15624
	TCCR1B = (1<<WGM12) | (1<<CS12); // set 1:256 prescaler, init CTC
	OCR1A  = 15624;			 // set counter
	TIMSK = (1<<OCIE1A);		 // enable timer interrupt

	// initialize beep time (1/6 second) [TODO]
	//   (((Input_Freq / Prescaler) / Target_Freq) - 1)
	//   (((4.000.000 / 1024) / 6) - 1) = 650.04
	//TCCR0B = (1<<CS12) | (1<<CS10);	// set 1:1024 prescaler
}


static inline int selected_timer()
{
	if(!(PIND & (1<<PORTD3)))
		return 0;
	else if(!(PIND & (1<<PORTD2)))
		return 1;
	return 2;
}


static void draw_7segment()
{
	int digit;
	int s = selected_timer();

	uint32_t time = (timer[s] % 60) + ((timer[s] / 60 % 60) * 100) +
		((timer[s] / 3600) * 10000);

	uint16_t r = 1;
	uint8_t seg = 0b00010000;
	for(digit=0; digit<5; digit++)
	{
		// draw number and activate corresponding digit
		uint8_t d = time / r % 10;
		if(digit == 4)
		{
			PORTD |= (1<<PORTD6);
			PORTB = d;
		}
		else
		{
			PORTD &= ~(1<<PORTD6);
			PORTB = seg | d;
		}

		// wait (more for numbers with more LEDs)
		if(d == 1)
			_delay_us(300);
		else if(d == 7)
			_delay_us(500);
		else
			_delay_ms(1);

		// next number
		r *= 10;
		seg <<= 1;
	}
}


static inline void adjust_timer(int amt)
{
	if(amt == 0)
		return;

	int s = selected_timer();
	timer[s] += amt;

	if(timer[s] < 0)
		timer[s] = 0;
	else if(timer[s] + amt > 60*60*9)
		timer[s] = 60*60*9;
}


static inline int updown_pressed()
{
	if(!(PIND & (1<<PORTD4)))
		return -2;
	else if(!(PIND & (1<<PORTD5)))
		return 2;
	return 0;
}


int main()
{
	// initialize variables and registers
	initialize();

	// enable interrupts
	sei();

	// main loop
	for(;;)
	{
		// TODO - beeps
		draw_7segment();
		adjust_timer(updown_pressed()); // TODO - check timing
	}

	return 0;
}


// interruption fired every one second
ISR(TIMER1_COMPA_vect)
{
	int i;
	for(i=0; i<3; i++)
	{
		if(timer[i] == 1)
			beep[i] = true;
		if(timer[i] != 0)
			--timer[i];
	}
}
