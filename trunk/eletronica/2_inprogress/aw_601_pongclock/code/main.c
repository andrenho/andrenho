#include <stdint.h>

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>

#define F_CPU 16000000UL
#include <util/delay.h>

// 74HC4094 commands
inline void CLK_0()   { PORTB &= ~(1<<PORTB4); }
inline void CLK_1()   { PORTB |=  (1<<PORTB4); }
inline void STR_0()   { PORTB &= ~(1<<PORTB5); }
inline void STR_1()   { PORTB |=  (1<<PORTB5); }
inline void OE_0()    { PORTD &= ~(1<<PORTD5); }
inline void OE_1()    { PORTD |=  (1<<PORTD5); }
inline void DATA0_0() { PORTB &= ~(1<<PORTB1); }
inline void DATA0_1() { PORTB |=  (1<<PORTB1); }
inline void DATA1_0() { PORTB &= ~(1<<PORTB0); }
inline void DATA1_1() { PORTB |=  (1<<PORTB0); }
inline void DATA2_0() { PORTB &= ~(1<<PORTB3); }
inline void DATA2_1() { PORTB |=  (1<<PORTB3); }
inline void DATA3_0() { PORTB &= ~(1<<PORTB2); }
inline void DATA3_1() { PORTB |=  (1<<PORTB2); }

// 4514 commands
inline void STRB_0()   { PORTD &= ~(1<<PORTD4); }
inline void STRB_1()   { PORTD |=  (1<<PORTD4); }
inline void D(unsigned char x) { PORTD = (PORTD & (0xf<<4)) | (x & 0xf); }

// LED display control
volatile int step = 0;
volatile uint32_t leds[16] = { 0 };

#define get_xy(x, y) (leds[y] & (1<<x))
/*
static inline int8_t get_xy(int x, int y) { 
	return leds[y] & (1<<x); 
}*/
static void set_xy(int x, int y, uint32_t v)
{
	if(v == 0) {
		leds[y] &= ~(1 << x);
	} else {
		leds[y] |= (1 << x);
	}
}


int main()
{
	DDRB = 0xff;
	DDRD = 0xff;

	int i;
	step = 0;
	for(i=0; i<16; i++)
		leds[i] = 0;

	// prepare timer to fire interrupt every 250us @16Mhz
	OCR2 = 254;
	TCCR2 |= (1<<WGM21);
	TIMSK |= (1<<OCIE2);
	TCCR2 |= (1<<CS21);
	sei();

	set_xy(2, 1, 1);
	set_xy(2, 2, 1);
	set_xy(3, 2, 1);
	set_xy(2, 9, 1);
	set_xy(18, 9, 1);

	// infinite loop
	for(;;) {
	}

	return 0;
}


// runs every 250us
ISR(TIMER2_COMP_vect)
{

	OE_0();

	// advance byte on the 4094
	STRB_0();
	D(15-step);
	STRB_1();

	// send data to 74HC4094
	int y;
	for(y=7; y>=0; y--) {
		CLK_1();
		if(get_xy(step, y)) {
			DATA0_1();
		} else {
			DATA0_0();
		}
		if(get_xy(step, y+8)) {
			DATA1_1();
		} else {
			DATA1_0();
		}
		if(get_xy(step+16, y)) {
			DATA2_1();
		} else {
			DATA2_0();
		}
		if(get_xy(step+16, y+8)) {
			DATA3_1();
		} else {
			DATA3_0();
		}
		CLK_0();
	}

	STR_0();
	STR_1();
	OE_1();

	step++;
	if(step == 16) {
		step = 0;
	}
}
