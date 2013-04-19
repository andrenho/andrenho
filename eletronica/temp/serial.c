#include <stdio.h>
#include <stdarg.h>

#define BAUD 9600
#define BAUD_PRESCALLER (((F_CPU / (BAUD * 16UL))) - 1)

void USART_init()
{
	UBRR0H = (uint8_t)(BAUD_PRESCALLER>>8);
	UBRR0L = (uint8_t)(BAUD_PRESCALLER);
	UCSR0B = (1<<RXEN0) | (1<<TXEN0);
	UCSR0C = ((1<<UCSZ00)|(1<<UCSZ01));
}


void USART_send(unsigned char data) 
{
	while(!(UCSR0A & (1<<UDRE0)))
		;
	UDR0 = data;
}


unsigned char USART_receive()
{
	while(!(UCSR0A & (1<<RXC0)))
		;
	return UDR0;
}


void USART_printf(char* fmt, ...)
{
	va_list args;
	char buffer[255];
	va_start(args, fmt);
	vsnprintf(buffer, 254, fmt, args);
	va_end(args);

	int i = 0;
	while(buffer[i] != 0) 
		USART_send(buffer[i++]);
}
