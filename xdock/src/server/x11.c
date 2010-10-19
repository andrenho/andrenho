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
	XEvent evt;

	wm->window = XCreateSimpleWindow(display,
			DefaultRootWindow(display),
			50, 50,   // origin
			64, 64,   // size
			0, white, // border
			white);  // backgd

	XMapWindow(display, wm->window);

	long eventMask = StructureNotifyMask;
	XSelectInput(display, wm->window, eventMask);
	do 
		XNextEvent(display, &evt);
	while(evt.type != MapNotify);

	return 1;
}


void x11_destroy_client(WM* wm)
{
	XEvent evt;

	long eventMask = StructureNotifyMask;
	XSelectInput(display, wm->window, eventMask);
	
	XDestroyWindow(display, wm->window);
	
	do 
		XNextEvent(display, &evt);
	while(evt.type != MapNotify);
}


void x11_quit()
{
	XCloseDisplay(display);
}


//
// Commands
//
int x11_draw_panel(WM* wm, int x1, int x2, int y1, int y2)
{
	return 1;
}
