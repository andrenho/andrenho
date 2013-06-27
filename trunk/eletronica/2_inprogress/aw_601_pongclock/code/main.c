#include <stdint.h>

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>

#define F_CPU 16000000UL
#include <util/delay.h>

/********
 * DATA *
 ********/

// LED display control
volatile int step = 0;
volatile int on_off = 0;

// time control
volatile int hours = 14;
volatile int minutes = 38;

// PONG control
volatile struct pong_t {
	uint8_t pad1   : 4;
	uint8_t pad2   : 4;
	uint8_t ball_x : 5;
	uint8_t ball_y : 4;
} pong;


/***********
 *  VIDEO  *
 ***********/
volatile uint16_t leds[32] = { 0 };

uint16_t numbers[] = {
//        0  1  2  3  4  
//        |  |  |  |  |
	0b111110111111101,
	0b101010001001101,
	0b101010111011111,
	0b101010100001001,
	0b111111111111001,
//        5  6  7  8  9
//        |  |  |  |  |
	0b111111111111111,
	0b100100001101101,
	0b111111011111111,
	0b001101001101001,
	0b111111001111001,
};

static void clear(void)
{
	int y;
	for(y=0; y<32; y++)
		leds[y] = 0;
}

static int get_xy(int x, int y) {
	if(x > 15) {
		y += 16;
		x -= 16;
	}
	return leds[y] & (1<<x); 
}

static void set_xy(int x, int y, uint32_t v)
{
	if(x > 15) {
		y += 16;
		x -= 16;
	}
	if(v == 0) {
		leds[y] &= ~(1 << x);
	} else {
		leds[y] |= (1 << x);
	}
}

static void draw_number(int x, int y, int n)
{
	int ydif=0;
	if(n < 0 || n > 9) {
		return;
	}
	if(n > 5) {
		n-=5;
		ydif=5;
	}

	int xx, yy;
	for(xx=0; xx<3; xx++) {
		for(yy=0; yy<5; yy++) {
			set_xy(x+2-xx, y+yy, 
					numbers[yy+ydif] & (1<<((4-n)*3+xx)));
		}
	}
}


/**************
 * IC CONTROL *
 **************/

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

// initialize microcontroller
void init_uc()
{
	// initialize ports
	DDRB = 0xff;
	DDRD = 0xff;

	// prepare timer to fire interrupt
	OCR2 = 60; // switch between 60 and 1 to change brightness
	TCCR2 |= (1<<WGM21);
	TIMSK |= (1<<OCIE2);
	TCCR2 |= (1<<CS22);
	sei();
}

// runs every x us, draw screen
ISR(TIMER2_COMP_vect)
{
	if(on_off++ % 2)
	{
		OE_0();

		// advance byte on the 4094
		STRB_0();
		D(15-step);

		// send data to 74HC4094
		int y;
		for(y=7; y>=0; y--) {
			CLK_0();
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
			CLK_1();
		}

		STRB_1();
		STR_0();
		STR_1();

		step++;
		if(step == 16) {
			step = 0;
		}
	} else {
		OE_1();
	}
}


/************
 *   PONG   *
 ************/
void pong_init(void)
{
	pong.pad1 = 6;
	pong.pad2 = 6;
	pong.ball_x = 2;
	pong.ball_y = 7;
}


void pong_draw(void)
{
	int y;

	clear();

	// pads
	for(y=pong.pad1; y<pong.pad1+4; y++) {
		set_xy(0, y, 1);
		set_xy(1, y, 1);
	}
	for(y=pong.pad2; y<pong.pad2+4; y++) {
		set_xy(30, y, 1);
		set_xy(31, y, 1);
	}

	// field
	for(y=1; y<16; y+=2) {
		set_xy(15, y, 1);
	}

	// ball
	set_xy(pong.ball_x, pong.ball_y, 1);

	// draw score
	draw_number( 7, 0, hours/10);
	draw_number(11, 0, hours % 10);
	draw_number(17, 0, minutes/10);
	draw_number(21, 0, minutes % 10);
}


void pong_process(void)
{
}


/*************
 *  GENERAL  *
 *************/
int main()
{
	// initialize variables and ics
	clear();
	pong_init();
	init_uc();

	// infinite loop
	pong_draw();
	for(;;) {
		_delay_ms(500);
		pong_process();
	}

	return 0;
}


