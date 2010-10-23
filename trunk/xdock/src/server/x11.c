#include "x11.h"

#include <X11/Xatom.h>
#include <stdio.h>
#include <stdlib.h>

#include "client.h"
#include "options.h"
#include "x11_cmd.h"
#include "x11_xpm.h"

Display* display;

static Colormap colormap;
static int white;
static int screen_w, screen_h;
static char** xpm_sq;
static int xrel, yrel;

static void x11_setup_colors(WM* wm);
static void x11_do_events_window(WM* wm, XEvent* evt);
static int x11_move_window(WM* wm, int x, int y);

void x11_initialize()
{
	XInitThreads();

	display = XOpenDisplay(NULL);
	if(!display)
	{
		fprintf(stderr, "Could not open display.\n");
		exit(1);
	}

	colormap = DefaultColormap(display, DefaultScreen(display));

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
	Atom atoms[2] = { None, None };
	atoms[0] = XInternAtom(display, "_NET_WM_WINDOW_TYPE_DOCK", False);
	XChangeProperty(display, wm->window,
			XInternAtom(display, "_NET_WM_WINDOW_TYPE", False),
			XA_ATOM, 32, PropModeReplace,
			(unsigned char*) atoms,
			1);

	// put window in the correct position in the screen
	wm->locked_column = -1;
	int x = screen_w - 96,
	    y = 0; // TODO - ?
	while(!x11_move_window(wm, x, y))
	{
		y += 96;
		if(y > screen_h + 96)
		{
			y = 0;
			x -= 96;
		}
	}

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

	// create GC
	wm->gc = XCreateGC(display, wm->window,
			0,        // mask of values
			NULL );   // array of values

	// create background square
	wm->pixmap = xpm_to_pixmap(xpm_sq, display, wm->window);
	XCopyArea(display, wm->pixmap, wm->window, wm->gc, 0, 0, 96, 96, 0, 0);
	XFlush(display);

	// setup colors
	x11_setup_colors(wm);

	return 1;
}


static inline int add_color(WM* wm, char* color)
{
	XColor xcolor;
	XParseColor(display, colormap, color, &xcolor);
	XAllocColor(display, colormap, &xcolor);
	wm->color[wm->n_colors++] = xcolor.pixel;
	return wm->n_colors-1;
}


static void x11_setup_colors(WM* wm)
{
	wm->n_colors = 0;
	add_color(wm, "black");
	add_color(wm, "white");
	add_color(wm, theme.panel_bg);
	add_color(wm, theme.panel_lt);
	add_color(wm, theme.panel_sw);
	add_color(wm, theme.unlit);
	add_color(wm, theme.lit);
	add_color(wm, theme.bright);
	add_color(wm, theme.glow);
	add_color(wm, theme.warning);
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


static int x11_move_window(WM* wm, int x, int y)
{
	Atom strut;
	unsigned long struts[12] = { 0, };

	// find the maximum locked color
	Client* c = clients;
	int max_column = -1;
	while(c)
	{
		if(&c->wm != wm)
			max_column = (max_column > c->wm.locked_column 
					? max_column 
					: c->wm.locked_column);
		c = c->next;
	}

	// confine window to the screen
	if(x < 0)
		x = 0;
	if(y < 0)
		y = 0;
	if(x > screen_w - 96)
		x = screen_w - 96;
	if(y > screen_h - 96)
		y = screen_h - 96;

	// check to see if it's on the attraction area
	int new_locked_column;
	if(x > screen_w - (96 * (max_column+2)) - opt.attract)
	{
		x = ((x - screen_w - 48) / 96) * 96 + screen_w;
		y = ((y+48) / 96) * 96;
		new_locked_column = ((screen_w - x) / 96 - 1);
	}
	else
		new_locked_column = -1;

	// refuse if there's another client in the same place
	XWindowAttributes xwa;
	c = clients;
	while(c)
	{
		XGetWindowAttributes(display, c->wm.window, &xwa);
		if(x == xwa.x && y == xwa.y)
			return 0;
		c = c->next;
	}

	if(new_locked_column != wm->locked_column)
	{
		wm->locked_column = new_locked_column;
		strut = XInternAtom(display, "_NET_WM_STRUT_PARTIAL", False);
		struts[1] = (wm->locked_column + 1) * 96;
		struts[6] = (wm->locked_column + 1) * 96;
		struts[7] = (wm->locked_column + 1) * 96;
		XChangeProperty(display, wm->window, strut, XA_CARDINAL, 32, 
				PropModeReplace, (unsigned char*)&struts, 12);
	}

	// move the window
	XMoveWindow(display, wm->window, x, y);
	return 1;
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
				Window wtmp; int tmp; unsigned int utmp;
				XQueryPointer(display, wm->window, &wtmp, &wtmp,
					&tmp, &tmp, &xrel, &yrel, &utmp);
				XRaiseWindow(display, wm->window);
			}
			break;

		case MotionNotify:
			if(evt->xmotion.state & Button1MotionMask)
			{
				x11_move_window(wm, 
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
