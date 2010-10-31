#include "font_led.h"

typedef struct {
	char ch; 
	char* model;
} FontModel;

static char* model_led2[] = {
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


void init_font(FontModel* model, char** xpm_model, XPM_Font* font)
{
}
