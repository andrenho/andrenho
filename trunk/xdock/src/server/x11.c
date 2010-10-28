#include "x11.h"

#include <X11/Xatom.h>
#include <stdio.h>
#include <stdlib.h>

#include "client.h"
#include "debug.h"
#include "options.h"
#include "x11_cmd.h"
#include "x11_util.h"

#include "font_led3.xpm"


Display* display;
Colormap colormap;

static int white;
static int screen_w, screen_h;
static char** xpm_sq;
static int xrel, yrel;

static void x11_do_events_client(Client* c, XEvent* evt);
static int x11_move_window(Client* c, int x, int y);
static void x11_initialize_colors(Client* c);
static void x11_initialize_fonts(Client* c);


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


int x11_setup_client(Client* c)
{
	XEvent evt;

	// create window
	c->window = XCreateSimpleWindow(display,
			DefaultRootWindow(display),
			0, 0,     // origin
			96, 96,   // size
			0, white, // border
			white);   // backgd

	// setup X11 properties
	Atom atoms[2] = { None, None };
	atoms[0] = XInternAtom(display, "_NET_WM_WINDOW_TYPE_DOCK", False);
	XChangeProperty(display, c->window,
			XInternAtom(display, "_NET_WM_WINDOW_TYPE", False),
			XA_ATOM, 32, PropModeReplace,
			(unsigned char*) atoms,
			1);

	// put window in the correct position in the screen
	c->locked_column = -1;
	int x = screen_w - 96,
	    y = 0;
	while(!x11_move_window(c, x, y))
	{
		y += 96;
		if(y > screen_h + 96)
		{
			y = 0;
			x -= 96;
		}
	}

	// map window
	XSelectInput(display, c->window, StructureNotifyMask);
	XMapWindow(display, c->window);
	do 
		XNextEvent(display, &evt);
	while(evt.type != MapNotify);

	// select input
	XSelectInput(display, c->window, ExposureMask 
					| StructureNotifyMask
					| PointerMotionMask
					| ButtonPressMask
					| ButtonReleaseMask);

	// create GC
	c->gc = XCreateGC(display, c->window,
			0,        // mask of values
			NULL );   // array of values

	// create background square
	c->pixmap = xpm_to_pixmap(xpm_sq, display, c);
	XCopyArea(display, c->pixmap, c->window, c->gc, 0, 0, 96, 96, 0, 0);
	XFlush(display);

	// initialize variables
	c->images = NULL;
	c->colors = NULL;
	c->fonts = NULL;
	x11_initialize_colors(c);
	x11_initialize_fonts(c);

	return 1;
}


static void x11_initialize_colors(Client *c)
{
	debug("Initializing colors...");

	struct ThemeColor* tc;
	for(tc = opt.colors; tc != NULL; tc = tc->hh.next)
	{
		XColor xcolor;
		XParseColor(display, colormap, tc->color, &xcolor); // TODO - check
		XAllocColor(display, colormap, &xcolor);

		struct Color* new_color = malloc(sizeof(struct Color));
		strcpy(new_color->name, tc->name);
		new_color->pixel = xcolor.pixel;
		HASH_ADD_STR(c->colors, name, new_color);
	}
}


static void x11_initialize_fonts(Client* c)
{
	int i;

	debug("Initializing fonts...");

	x11_new_font(c, "led3");
	i = 0;
	while(font_led3[i].xpm)
	{
		Pixmap p = xpm_to_pixmap(font_led3[i].xpm, display, c);
		if(p)
			x11_font_char(c, "led3", font_led3[i].c, p);
		i++;
	}
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
			if(c->window == evt.xany.window)
			{
				x11_do_events_client(c, &evt);
				break;
			}
			c = c->next;
		}
	}
}


static int x11_move_window(Client* c, int x, int y)
{
	Atom strut;
	unsigned long struts[12] = { 0, };

	// find the maximum locked column
	Client* client = clients;
	int max_column = -1;
	while(client)
	{
		if(client != c)
			max_column = (max_column > client->locked_column 
					? max_column 
					: client->locked_column);
		client = client->next;
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
	client = clients;
	while(client)
	{
		XGetWindowAttributes(display, client->window, &xwa);
		if(x == xwa.x && y == xwa.y)
			return 0;
		client = client->next;
	}

	if(new_locked_column != c->locked_column)
	{
		c->locked_column = new_locked_column;
		strut = XInternAtom(display, "_NET_WM_STRUT_PARTIAL", False);
		struts[1] = (c->locked_column + 1) * 96;
		struts[6] = (c->locked_column + 1) * 96;
		struts[7] = (c->locked_column + 1) * 96;
		XChangeProperty(display, c->window, strut, XA_CARDINAL, 32, 
				PropModeReplace, (unsigned char*)&struts, 12);
	}

	// move the window
	XMoveWindow(display, c->window, x, y);
	return 1;
}


static void x11_do_events_client(Client* c, XEvent* evt)
{
	switch(evt->type)
	{
		case Expose:
			break;

		case ButtonPress:
			if(evt->xbutton.button == Button1)
			{
				Window wtmp; int tmp; unsigned int utmp;
				XQueryPointer(display, c->window, &wtmp, 
						&wtmp, &tmp, &tmp, &xrel, 
						&yrel, &utmp);
				XRaiseWindow(display, c->window);
			}
			x11_pointer_event(c, "down", evt->xbutton.x,
					evt->xbutton.y);
			break;

		case ButtonRelease:
			x11_pointer_event(c, "up", evt->xbutton.x,
					evt->xbutton.y);
			break;

		case MotionNotify:
			if(evt->xmotion.state & Button1MotionMask)
			{
				x11_move_window(c, 
						evt->xmotion.x_root - xrel,
						evt->xmotion.y_root - yrel);
			}
			break;
	}
}


void x11_destroy_client(Client* c)
{
	XDestroyWindow(display, c->window);
	debug("Client window destroyed.");
	// TODO - clear stored images/fonts
}


void x11_quit()
{
	XCloseDisplay(display);
}
