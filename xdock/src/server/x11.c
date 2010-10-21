#include "x11.h"

#include <X11/Xatom.h>
#include <stdio.h>
#include <stdlib.h>

#include "x11_xpm.h"
#include "options.h"
#include "client.h"

static Display* display;
static int white;
static int screen_w, screen_h;
static char** xpm_sq;
static int xrel, yrel;

static void x11_do_events_window(WM* wm, XEvent* evt);

void x11_initialize()
{
	XInitThreads();

	display = XOpenDisplay(NULL);
	if(!display)
	{
		fprintf(stderr, "Could not open display.\n");
		exit(1);
	}

	white = WhitePixel(display, DefaultScreen(display));

	screen_w = XDisplayWidth(display, DefaultScreen(display));
	screen_h = XDisplayHeight(display, DefaultScreen(display));

	xpm_sq = square_xpm(opt.dock_color);
}


int x11_setup_client(WM* wm)
{
	XEvent evt;

	// create window
	wm->window = XCreateSimpleWindow(display,
			DefaultRootWindow(display),
			0, 0,     // origin
			96, 96,   // size
			0, white, // border
			white);   // backgd

	// setup X11 properties
	Atom atoms[2] = { None, None }, strut;
	unsigned long struts[12] = { 0, };

	atoms[0] = XInternAtom(display, "_NET_WM_WINDOW_TYPE_DOCK", False);
	XChangeProperty(display, wm->window,
			XInternAtom(display, "_NET_WM_WINDOW_TYPE", False),
			XA_ATOM, 32, PropModeReplace,
			(unsigned char*) atoms,
			1);
	/*
	strut = XInternAtom(display, "_NET_WM_STRUT_PARTIAL", False);
	struts[1] = 96;
	struts[6] = 96;
	struts[7] = 96;
	XChangeProperty(display, wm->window, strut, XA_CARDINAL, 32, PropModeReplace,
			(unsigned char*)&struts, 12);
	*/

	// map window
	XSelectInput(display, wm->window, StructureNotifyMask);
	XMapWindow(display, wm->window);
	do 
		XNextEvent(display, &evt);
	while(evt.type != MapNotify);

	// select input
	XSelectInput(display, wm->window, ExposureMask 
					| StructureNotifyMask
					| PointerMotionMask
					| ButtonPressMask
					| ButtonReleaseMask);

	XResizeWindow(display, wm->window, 96, 96);

	// create GC
	wm->gc = XCreateGC(display, wm->window,
			0,        // mask of values
			NULL );   // array of values

	// create background square
	wm->pixmap = xpm_to_pixmap(xpm_sq, display, wm->window);
	XCopyArea(display, wm->pixmap, wm->window, wm->gc, 0, 0, 96, 96, 0, 0);

	return 1;
}


void x11_do_events()
{
	XEvent evt;

	while(XPending(display))
	{
		XNextEvent(display, &evt);

		Client* c = clients;
		while(c)
		{
			if(c->wm.window == evt.xany.window)
			{
				x11_do_events_window(&c->wm, &evt);
				break;
			}
			c = c->next;
		}
	}
}


static void x11_do_events_window(WM* wm, XEvent* evt)
{
	switch(evt->type)
	{
		case Expose:
			break;
		case ButtonPress:
			if(evt->xbutton.button == Button1)
			{
				Window wtmp;
				int tmp;
				unsigned int utmp;
				XQueryPointer(display, wm->window, &wtmp, &wtmp,
					&tmp, &tmp, &xrel, &yrel, &utmp);
			}
			break;
		case MotionNotify:
			if(evt->xmotion.state & Button1MotionMask)
			{
				XRaiseWindow(display, wm->window);
				XMoveWindow(display, wm->window,
						evt->xmotion.x_root - xrel,
						evt->xmotion.y_root - yrel);
			}
			break;
	}
}


void x11_destroy_client(WM* wm)
{
	/*
	XEvent evt;

	long eventMask = StructureNotifyMask;
	XSelectInput(display, wm->window, eventMask);
	*/
	XDestroyWindow(display, wm->window);
	/*
	do 
		XNextEvent(display, &evt);
	while(evt.type != MapNotify);
	*/
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
