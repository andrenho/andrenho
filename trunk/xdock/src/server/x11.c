#include "x11.h"

#include <stdio.h>

static Display* display;
static int white;
static int screen_w, screen_h;

void x11_initialize()
{
	XInitThreads();

	display = XOpenDisplay(NULL);
	if(!display)
	{
		fprintf(stderr, "Could not open display.\n");
		return 0;
	}

	white = WhitePixel(display, DefaultScreen(display));

	screen_w = XDisplayWidth(display, DefaultScreen(display));
	screen_h = XDisplayHeight(display, DefaultScreen(display));
}


int x11_setup_client(WM* wm)
{
	return 1;
}


void x11_destroy_client(WM* wm)
{
}


void x11_quit()
{
}


//
// Commands
//
int x11_draw_panel(WM* wm, int x1, int x2, int y1, int y2)
{
	return 1;
}
