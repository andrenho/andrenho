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
	wm->window = XCreateSimpleWindow(display,
			DefaultRootWindow(display),
			50, 50,   // origin
			64, 64,   // size
			0, white, // border
			white);  // backgd

	XMapWindow(display, wm->window);

	long eventMask = StructureNotifyMask;
/*
XSelectInput( dsp, win, eventMask );
 
  XEvent evt;
  do{
    XNextEvent( dsp, &evt );   // calls XFlush
  }while( evt.type != MapNotify );
 
 
  GC gc = XCreateGC( dsp, win,
                     0,        // mask of values
                     NULL );   // array of values
  XSetForeground( dsp, gc, black );
 
 
  XDrawLine(dsp, win, gc, 10, 10,190,190); //from-to
  XDrawLine(dsp, win, gc, 10,190,190, 10); //from-to
 
 
  eventMask = ButtonPressMask|ButtonReleaseMask;
  XSelectInput(dsp,win,eventMask); // override prev
 
  do{
    XNextEvent( dsp, &evt );   // calls XFlush()
  }while( evt.type != ButtonRelease );
 
 
  XDestroyWindow( dsp, win );
  XCloseDisplay( dsp );
*/

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
