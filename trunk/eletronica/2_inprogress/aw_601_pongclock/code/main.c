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
inline void DATA0_0() { PORTB &= ~(1<<PORTB0); }
inline void DATA0_1() { PORTB |=  (1<<PORTB0); }
inline void DATA1_0() { PORTB &= ~(1<<PORTB1); }
inline void DATA1_1() { PORTB |=  (1<<PORTB1); }
inline void DATA2_0() { PORTB &= ~(1<<PORTB2); }
inline void DATA2_1() { PORTB |=  (1<<PORTB2); }
inline void DATA3_0() { PORTB &= ~(1<<PORTB3); }
inline void DATA3_1() { PORTB |=  (1<<PORTB3); }

// 4514 commands
inline void STRB_0()   { PORTD &= ~(1<<PORTD4); }
inline void STRB_1()   { PORTD |=  (1<<PORTD4); }
inline void D(unsigned char x) { PORTD = (PORTD & (0xf<<4)) | (x & 0xf); }

int main()
{
	DDRB = 0xff;
	DDRD = 0xff;

	// initialize
	DATA3_0();
	CLK_0();
	STR_0();
	OE_0();

	// send data to 74HC4094
	unsigned char i=0;
	for(i=0; i<8; i++)
	{
		DATA3_1();
		CLK_1();
		CLK_0();
	}
	STR_1();
	OE_1();

	// send data to 4094
	while(1)
	{
		for(i=0; i<16; i++)
		{
			STRB_1();
			D(i);
			STRB_0();
			//_delay_us(5);
		}
	}

	return 0;
}
