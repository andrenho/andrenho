#ifndef FONT_LED_H
#define FONT_LED_H

typedef struct {
	unsigned char c;
	char** xpm;
} XPM_Font;

extern XPM_Font *lcd3, led4[];

void font_led_init();

#endif
