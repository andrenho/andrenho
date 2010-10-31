#include "font_led.h"

#include "font_led3.xpm"


typedef struct {
	char ch; 
	char* model;
} FontModel;

static char* led2_xpm_model[] = {
"12 20 3 1",
" 	c #1B1B1B s panel_bg",
".	c #004840 s unlit",
"o	c #20B0A8 s bright",
"  000000    ",
"1  0000  2  ",
"11      22  ",
"11      22  ",
"11      22  ",
"11      22  ",
"11      22  ",
"11      22  ",
"11      22  ",
"1  3333  2  ",
"  333333    ",
"4        5  ",
"44      55  ",
"44      55  ",
"44      55  ",
"44      55  ",
"44      55  ",
"44      55  ",
"4  6666  5  ",
"  666666    "
};


FontModel led2_model[] = {
	{ ' ', "" },
	{ '0', "12456" },
};


XPM_Font* led2;


XPM_Font* init_font(FontModel* model, char** xpm_model)
{
	XPM_Font* led2 = malloc(sizeof(XPM_Font) *
		       	(sizeof(xpm_model) / sizeof(FontModel)));

	return led2;
}


void font_led_init()
{
	led2 = init_font(led2_model, led2_xpm_model);
}
