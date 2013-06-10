#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>

#define F_CPU 16000000UL
#include <util/delay.h>

#include "usbdrv.h"

#define USB_LED_OFF 0
#define USB_LED_ON  1

#define USB_DATA_OUT 2
static uchar replyBuf[16] = "Hello, USB!";


USB_PUBLIC uchar usbFunctionSetup(uchar data[8])
{
	usbRequest_t *rq = (void*)data;
	switch(rq->bRequest)
	{
		case USB_LED_ON:
			PORTC |= 1;
			return 0;
		case USB_LED_OFF:
			PORTC &= ~1;
			return 0;
		case USB_DATA_OUT: // send data to PC
			usbMsgPtr = replyBuf;
			return sizeof(replyBuf);
	}

	return 0;
}

int main()
{
	uchar i;

	DDRC = 1;

	wdt_enable(WDTO_1S);

	usbInit();

	usbDeviceDisconnect();
	for(i=0; i<250; i++)
	{
		wdt_reset();
		_delay_ms(1);
	}
	usbDeviceConnect();
		PORTC |= 1;


	sei();

	while(1)
	{
		wdt_reset();
		usbPoll();
	}

	return 0;
}
