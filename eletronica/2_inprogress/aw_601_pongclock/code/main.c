#include <stdint.h>
#include <stdlib.h>

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>

#define F_CPU 16000000UL
#include <util/delay.h>

#include <i2cmaster.h>

#define DS1307_ADDRESS (0b11010000)
#define DS1307_READ  (DS1307_ADDRESS | 1)
#define DS1307_WRITE (DS1307_ADDRESS | 0)

/********
 * DATA *
 ********/

// LED display control
volatile int step = 0;
volatile int on_off = 0;
volatile int bright = 1;
volatile int bigclock = 0;

// time control
volatile uint8_t hours = 0;
volatile uint8_t minutes = 0;
volatile uint8_t seconds = 0;
volatile int read_clock = 0;

// PONG control
volatile struct pong_t {
	uint8_t pad1         : 4;
	uint8_t pad2         : 4;
	uint8_t ball_x       : 5;
	uint8_t ball_y       : 4;
	uint8_t last_ball1_x : 5;
	uint8_t last_ball1_y : 4;
	uint8_t last_ball2_x : 5;
	uint8_t last_ball2_y : 4;
	 int8_t ball_dir_x   : 2;
	 int8_t ball_dir_y   : 4;
         int8_t prepare1     : 5;
         int8_t prepare2     : 5;
	uint8_t change_min   : 1;
	uint8_t change_hr    : 1;
} pong;

/*********
 * FONTS *
 *********/
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

uint8_t numbers_big[10][14] = {
	{ 0b00110000,
	  0b01111000,
	  0b11001100,
	  0b11001100,
	  0b11001100,
	  0b11001100,
	  0b11001100,
	  0b11001100,
	  0b01111000,
	  0b00110000 },
	{ 0b00110000,
	  0b01110000,
	  0b11110000,
	  0b00110000,
	  0b00110000,
	  0b00110000,
	  0b00110000,
	  0b00110000,
	  0b00110000,
	  0b11111100 },
	{ 0b00110000,
	  0b01111000,
	  0b11001100,
	  0b00001100,
	  0b00001100,
	  0b00011000,
	  0b00110000,
	  0b01100000,
	  0b11000000,
	  0b11111100 },
	{ 0b11111100,
	  0b00001100,
	  0b00011000,
	  0b00110000,
	  0b01110000,
	  0b00011000,
	  0b00001100,
	  0b00001100,
	  0b11011000,
	  0b01110000 },
	{ 0b00011000,
	  0b00111000,
	  0b01111000,
	  0b01011000,
	  0b11011000,
	  0b11011000,
	  0b11111100,
	  0b00011000,
	  0b00011000,
	  0b00011000 },
	{ 0b11111100,
	  0b11000000,
	  0b11000000,
	  0b11000000,
	  0b11111000,
	  0b00001100,
	  0b00001100,
	  0b00001100,
	  0b11001100,
	  0b01111000 },
	{ 0b00111100,
	  0b01100000,
	  0b11000000,
	  0b11000000,
	  0b11111000,
	  0b11001100,
	  0b11001100,
	  0b11001100,
	  0b01101100,
	  0b00111000 },
	{ 0b11111100,
	  0b00001100,
	  0b00011000,
	  0b00011000,
	  0b00110000,
	  0b00110000,
	  0b01100000,
	  0b01100000,
	  0b01100000,
	  0b01100000 },
	{ 0b00110000,
	  0b01111000,
	  0b11001100,
	  0b01111000,
	  0b00110000,
	  0b01111000,
	  0b11001100,
	  0b11001100,
	  0b01111000,
	  0b00110000 },
	{ 0b00110000,
	  0b01111000,
	  0b11001100,
	  0b11001100,
	  0b01111100,
	  0b00111100,
	  0b00001100,
	  0b00001100,
	  0b00011000,
	  0b01110000 },
};


/***********
 *  VIDEO  *
 ***********/
volatile uint16_t leds[32] = { 0 };

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
	if(x < 0 || y < 0 || x > 31 || y > 15)
		return;
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
	if(n > 4) {
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

static void draw_bignumber(int x, int y, int n)
{
	if(n < 0 || n > 9)
		return;
	int xx, yy;
	for(xx=0; xx<6; xx++) {
		for(yy=0; yy<10; yy++) {
			set_xy(x+xx, y+yy, numbers_big[n][yy] & (1<<(7-xx)));
		}
	}
}


/**********
 *  TIME  *
 **********/
void read_time()
{

	unsigned char n;

	// read minutes
	i2c_start_wait(DS1307_WRITE);
	i2c_write(0x1);
	i2c_rep_start(DS1307_READ);
	n = i2c_readNak();
	int m = ((n >> 4) * 10) + (n & 0b1111);

	// read hours
	i2c_rep_start(DS1307_WRITE);
	i2c_write(0x2);
	i2c_rep_start(DS1307_READ);
	n = i2c_readNak();
	int h = (n & 0b1111);
	if(n & 0b100000)
		h += 20;
	else if(n & 0b10000)
		h += 10;
	i2c_stop();

	// check for change
	if(h != hours) {
		pong.change_hr = 1;
	} else if(m != minutes) {
		pong.change_min = 1;
	}
}


void read_time_initial()
{
	unsigned char n;

	// read minutes
	i2c_start_wait(DS1307_WRITE);
	i2c_write(0x1);
	i2c_rep_start(DS1307_READ);
	n = i2c_readNak();
	minutes = ((n >> 4) * 10) + (n & 0b1111);

	// read hours
	i2c_rep_start(DS1307_WRITE);
	i2c_write(0x2);
	i2c_rep_start(DS1307_READ);
	n = i2c_readNak();
	hours = (n & 0b1111);
	if(n & 0b100000)
		hours += 20;
	else if(n & 0b10000)
		hours += 10;
	i2c_stop();

	pong.change_min = 0;
	pong.change_hr = 0;
}


void save_time()
{
	// seconds
	i2c_start_wait(DS1307_WRITE);
	i2c_write(0x0);
	i2c_write(0b00000000);
	i2c_stop();

	// minutes
	i2c_start_wait(DS1307_WRITE);
	i2c_write(0x1);
	i2c_write((minutes % 10) | ((minutes / 10) << 4));
	i2c_stop();

	// hours
	i2c_start_wait(DS1307_WRITE);
	i2c_write(0x2);
	i2c_write((hours % 10) 
			| ((hours >= 10 && hours < 20) ? 0b010000 : 0)
			| ((hours >= 20) ? 0b100000 : 0)
			| 0b0000000);
	i2c_stop();

	read_time_initial();
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

	// setup the ADC
	ADMUX = 0x03; // use PC3
	ADMUX |= (1<<REFS0);
	ADMUX &= ~(1<<ADLAR);
	ADCSRA |= ((1<<ADPS2)|(1<<ADPS0));
	ADCSRA |= (1<<ADEN);

	// prepare timer to fire interrupt
	OCR2 = 60; // switch between 60 and 1 to change brightness
	TCCR2 |= (1<<WGM21);
	TIMSK |= (1<<OCIE2);
	TCCR2 |= (1<<CS22);

	// prepare timer to advance seconds
	OCR1A = 15624;
	TCCR1B |= (1 << WGM12);
	TIMSK |= (1 << OCIE1A);
	TCCR1B |= (1 << CS12) | (1 << CS10);

	// activate interrupts
	sei();

	// initialize I²C
	i2c_init();
}

ISR(TIMER1_COMPA_vect)
{
	read_clock = 1;
	++seconds;
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
		if(!bright) {
			_delay_us(20);
			OE_0();
		}
	}
}


void read_button(int adc)
{
	/* buttons:
	 *   none = 0
	 *   1 = 1023
	 *   2 = 870
	 *   3 = 1003
	 *   4 = 960 */
	if(adc > 1015) { // brigthness
		bright = !bright;
		_delay_ms(50);
	} else if(adc > 980) { // hours
		hours++;
		if(hours > 23) {
			hours = 0;
		}
		save_time();
		_delay_ms(50);
	} else if(adc > 920) { // minutes
		minutes++;
		if(minutes > 59) {
			minutes = 0;
			hours++;
		}
		if(hours > 23) {
			hours = 0;
		}
		save_time();
		_delay_ms(50);
	} else if(adc > 800) { // mode
		clear();
		bigclock = !bigclock;
		_delay_ms(50);
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
	pong.ball_dir_x = 1;
	pong.ball_dir_y = -4;
	pong.change_min = 0;
	pong.change_hr = 0;
}


void pong_draw(void)
{
	int y;

	// ball
	set_xy(pong.last_ball2_x, pong.last_ball2_y, 0);
	set_xy(pong.last_ball1_x, pong.last_ball1_y, 1);
	set_xy(pong.ball_x, pong.ball_y, 1);

	// pads
	set_xy(0, pong.pad1-1, 0);
	set_xy(1, pong.pad1-1, 0);
	for(y=pong.pad1; y<pong.pad1+4; y++) {
		set_xy(0, y, 1);
		set_xy(1, y, 1);
	}
	set_xy(0, pong.pad1+4, 0);
	set_xy(1, pong.pad1+4, 0);

	set_xy(30, pong.pad2-1, 0);
	set_xy(31, pong.pad2-1, 0);
	for(y=pong.pad2; y<pong.pad2+4; y++) {
		set_xy(30, y, 1);
		set_xy(31, y, 1);
	}
	set_xy(30, pong.pad2+4, 0);
	set_xy(31, pong.pad2+4, 0);

	// field
	for(y=1; y<16; y+=2) {
		set_xy(15, y, 1);
	}

	// draw score
	draw_number( 7, 0, hours/10);
	draw_number(11, 0, hours % 10);
	draw_number(17, 0, minutes/10);
	draw_number(21, 0, minutes % 10);

	// draw adc
	/*
	clear();
	draw_number(3, 11, adc/1000);
	draw_number(7, 11, adc%1000/100);
	draw_number(11, 11, adc%100/10);
	draw_number(15, 11, adc%10);
	*/
}


void pong_prepare_movement(void)
{
	int pad1=0, pad2=0;
	if(pong.ball_x <= 5 && pong.ball_dir_x == -1) {
		pad1 = 2; pad2 = 0;
	} else if(pong.ball_x >= 26 && pong.ball_dir_x == 1) {
		pad1 = 0; pad2 = 2;
	} else if(pong.ball_x < 22 && pong.ball_dir_x < 0) {
		pad1 = rand() < (RAND_MAX/8);
		pad2 = rand() < (RAND_MAX/30);
	} else if(pong.ball_x > 10 && pong.ball_dir_x > 0) {
		pad1 = rand() < (RAND_MAX/30);
		pad2 = rand() < (RAND_MAX/8);
	}

	int dif = (rand() % 4) - 3;

	if(pad1) {
		if(pong.change_min) {
			if(pong.ball_x == 8) {
				pong.prepare1 = 2;
			}
		} else {
			pong.prepare1 = pong.ball_y + dif;
		}
	} else {
		pong.prepare1 = pong.pad1;
	}
	if(pad2) {
		if(pong.change_hr) {
			if(pong.ball_x == 24) {
				pong.prepare2 = 2;
			}
		} else {
			pong.prepare2 = pong.ball_y + dif;
		}
	} else {
		pong.prepare2 = pong.pad2;
	}
}


void pong_move_ball(void)
{
	// save last position
	pong.last_ball2_x = pong.last_ball1_x;
	pong.last_ball2_y = pong.last_ball1_y;
	pong.last_ball1_x = pong.ball_x;
	pong.last_ball1_y = pong.ball_y;

	// vertical movement, collision with top and bottom
	if(pong.ball_x % pong.ball_dir_y == 0) {
		if(pong.ball_dir_y > 0) {
			if(pong.ball_y == 15) {
				pong.ball_y--;
				pong.ball_dir_y = -pong.ball_dir_y;
			} else {
				pong.ball_y++;
			}
		} else {
			if(pong.ball_y == 0) {
				pong.ball_y++;
				pong.ball_dir_y = -pong.ball_dir_y;
			} else {
				pong.ball_y--;
			}
		}
	}

	// horizontal movement
	pong.ball_x += pong.ball_dir_x;

	// pad collisiion
	if(pong.ball_x == 2
	&& ((pong.ball_y >= pong.pad1 && pong.ball_y < pong.pad1+4) || !pong.change_min))  {
		pong.ball_dir_x = 1;
		if(pong.ball_y == pong.pad1) {
			pong.ball_dir_y = -2;
		} else if(pong.ball_y == pong.pad1+1) {
			pong.ball_dir_y = -4;
		} else if(pong.ball_y == pong.pad1+2) {
			pong.ball_dir_y = 4;
		} else if(pong.ball_y == pong.pad1+3) {
			pong.ball_dir_y = 2;
		}
		pong.last_ball1_x = 2; // makes movement realistic
		pong.ball_x = 3;
	} else if(pong.ball_x == 29 
	&& ((pong.ball_y >= pong.pad2 && pong.ball_y < pong.pad2+4) || !pong.change_hr)) {
		pong.ball_dir_x = -1;
		if(pong.ball_y == pong.pad2) {
			pong.ball_dir_y = -2;
		} else if(pong.ball_y == pong.pad2+1) {
			pong.ball_dir_y = -4;
		} else if(pong.ball_y == pong.pad2+2) {
			pong.ball_dir_y = 4;
		} else if(pong.ball_y == pong.pad2+3) {
			pong.ball_dir_y = 2;
		}
	}

	// score!
	if(pong.ball_x == 31 && pong.change_hr) {
		minutes = 0;
		if(hours == 23) {
			hours = 0;
		} else {
			hours++;
		}
		read_time();
		pong.ball_x = 2;
		pong.ball_y = 7;
		pong.ball_dir_x = 1;
		pong.ball_dir_y = -4;
		pong.change_hr = 0;
		read_time_initial();
	}
	if(pong.ball_x == 0 && pong.change_min) {
		minutes++;
		pong.ball_x = 29;
		pong.ball_y = 7;
		pong.ball_dir_x = -1;
		pong.ball_dir_y = -4;
		pong.change_min = 0;
		read_time_initial();
	}

	// prepare pad movement
	pong_prepare_movement();
}


void pong_move_pad(void)
{
	if(pong.pad1 > pong.prepare1 && pong.pad1 > 0) {
		pong.pad1--;
	} else if(pong.pad1 < pong.prepare1 && pong.pad1 < 12) {
		pong.pad1++;
	}
	if(pong.pad2 > pong.prepare2 && pong.pad2 > 0) {
		pong.pad2--;
	} else if(pong.pad2 < pong.prepare2 && pong.pad2 < 12) {
		pong.pad2++;
	}
}


/*************
 * BIG CLOCK *
 *************/
void bigclock_draw()
{
	draw_bignumber(1, 3, hours/10);
	draw_bignumber(8, 3, hours%10);
	draw_bignumber(18, 3, minutes/10);
	draw_bignumber(25, 3, minutes%10);

	int n = seconds % 2;
	int x, y;
	for(x=15; x<=16; x++) {
		for(y=5; y<=6; y++) {
			set_xy(x, y, n);
			set_xy(x, y+4, n);
		}
	}
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
	read_time_initial();

	// infinite loop
	//int c = 0;
	for(;;) {
		ADCSRA |= (1<<ADSC);          // prepare to read button (ADC)
		while(ADCSRA & (1<<ADSC)) {   // wait for ADC response
			int i;
			for(i=0; i<2; i++) {
				if(bigclock) {
					bigclock_draw();
				} else {
					pong_draw();
				}
				_delay_ms(25);
				pong_move_pad();
			}
			pong_move_ball();
		}
		
		read_button(ADCW);

		if(read_clock) {
			read_time();
			read_clock = 0;
		}
	}

	return 0;
}
