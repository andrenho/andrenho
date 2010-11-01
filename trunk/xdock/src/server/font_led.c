#include "font_led.h"

#include <stdio.h>
#include <string.h>

#include "font_led3.xpm"


static char* led2_xpm_model[] = {
"12 20 10 1",
" 	c #1B1B1B s panel_bg",
"0	c #004840 s unlit",
"1	c #004840 s unlit",
"2	c #004840 s unlit",
"3	c #004840 s unlit",
"4	c #004840 s unlit",
"5	c #004840 s unlit",
"6	c #004840 s unlit",
"7	c #004840 s panel_bg",
"8	c #004840 s panel_bg",
"  000000    ",
"1  0000  2  ",
"11      22  ",
"11    7 22  ",
"11   77 22  ",
"11  77  22  ",
"11 77   22  ",
"11 7    22  ",
"11      22  ",
"1  3333  2  ",
"  333333    ",
"4        5  ",
"44 8    55  ",
"44 88   55  ",
"44  88  55  ",
"44   88 55  ",
"44    8 55  ",
"44      55  ",
"4  6666  5  ",
"  666666    "
};


typedef struct {
	char ch; 
	char* model;
} FontModel;

/*  0
 * 1 2
 *  3
 * 4 5
 *  6  */
FontModel led2_model[] = {
	{ ' ', "" },
	{ '0', "012456" },
	{ '1', "25" },
	{ '2', "02346" },
	{ '3', "02356" },
	{ '4', "1235" },
	{ '5', "01356" },
	{ '6', "013456" },
	{ '7', "025" },
	{ '8', "0123456" },
	{ '9', "012356" },
	{ 'A', "012345" },
	{ 'B', "13456" },
	{ 'C', "0146" },
	{ 'D', "23456" },
	{ 'E', "01346" },
	{ 'F', "0134" },
	{ 'G', "013456" },
	{ 'H', "12345" },
	{ 'I', "14" },
	{ 'J', "2456" },
	{ 'K', "1478" },
	{ 'L', "146" },
	{ 'M', "" },
	{ 'N', "01245" },
	{ 'O', "012456" },
	{ 'P', "01234" },
	{ 'Q', "0124568" },
	{ 'R', "012348" },
	{ 'S', "01356" },
	{ 'T', "1346" },
	{ 'U', "12456" },
	{ 'V', "1258" },
	{ 'W', "" },
	{ 'X', "" },
	{ 'Y', "1235" },
	{ 'Z', "0467" },
	{ '\0', NULL }
};


XPM_Font* led2;


XPM_Font* init_font(FontModel* model, char** xpm_model)
{
	XPM_Font* xpm_font = malloc(sizeof(XPM_Font) *
		       	(sizeof(xpm_model) / sizeof(FontModel) + 1));

	int i, j;
	for(i=0; model[i].ch; i++)
	{
		// setup char
		xpm_font[i].c = model[i].ch;

		// create model
		int w, h, ncols, szcol;
		sscanf(xpm_model[0], "%d %d %d %d", &w, &h, &ncols, &szcol);
		xpm_font[i].xpm = malloc(sizeof(char*) * (1 + ncols + h));
		xpm_font[i].xpm[0] = strdup(xpm_model[0]);
		xpm_font[i].xpm[1] = strdup(xpm_model[1]);

		// colors
		for(j=2; j < 1+ncols; j++)
		{
			char ch = xpm_model[j][0];
			if(strchr(model[i].model, ch))
			{
				xpm_font[i].xpm[j] = malloc(sizeof(char) * 40);
				sprintf(xpm_font[i].xpm[j], "%c\tc #20B0A8 s bright", ch);
			}
			else
				xpm_font[i].xpm[j] = strdup(xpm_model[j]);
		}

		// rest of the xpm
		for(j=1+ncols; j<1+ncols+h; j++)
			xpm_font[i].xpm[j] = strdup(xpm_model[j]);

//		printf("---------------------\n");
//		for(j=0; j<1+ncols+h; j++)
//			printf("--- %s\n", xpm_font[i].xpm[j]);
	}
	xpm_font[i].c = '\0';
	xpm_font[i].xpm = NULL;

	return xpm_font;
}


void font_led_init()
{
	led2 = init_font(led2_model, led2_xpm_model);
}
