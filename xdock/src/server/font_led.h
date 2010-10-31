#ifndef FONT_LED_H
#define FONT_LED_H

typedef struct {
	unsigned char c;
	char** xpm;
} XPM_Font;

extern XPM_Font *led2, led3[];

void font_led_init();

#endif
