#include "x11.h"

#include <X11/Xatom.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "client.h"
#include "debug.h"
#include "font_led.h"
#include "options.h"
#include "x11_cmd.h"
#include "x11_util.h"


Display* display;		// the X display
Colormap colormap;		// colormap of the display

static int white;		// white color index
static int screen_w, screen_h;	// size of the screen, in pixels
static int top_y;		// height of a possible top dock
static char** xpm_sq;		// XPM image of the docks
static int xrel, yrel;		// last click, used to control dragging


// Function prototypes
static void x11_do_events_client(Client* c, XEvent* evt);
static int x11_move_window(Client* c, int x, int y);
static int x11_initialize_colors(Client* c);
static int x11_initialize_fonts(Client* c);
static int x11_panel_height(Window window);


// Initialize X11 display.
void x11_initialize()
{
	// Initialize display
	display = XOpenDisplay(NULL);
	if(!display)
	{
		fprintf(stderr, "Could not open display.\n");
		exit(1);
	}
	
	// Get basic information about the screen
	colormap = DefaultColormap(display, DefaultScreen(display));

	white = WhitePixel(display, DefaultScreen(display));

	screen_w = XDisplayWidth(display, DefaultScreen(display));
	screen_h = XDisplayHeight(display, DefaultScreen(display));

	// Get the size of the upper panel
	top_y = x11_panel_height(RootWindow(display, DefaultScreen(display)));

	// Create the dock background image (XPM)
	xpm_sq = square_xpm(opt.dock_color);

	// initialize fonts
	debug("Initializing all fonts.");
	font_led_init();
}


// This function is called when a client connects. It creates and setup the
// window of the dock.
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
	    y = top_y;
	while(!x11_move_window(c, x, y))
	{
		y += 96;
		if(y > screen_h + 96)
		{
			y = top_y;
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
	if(!x11_initialize_colors(c))
		return 0;
	if(!x11_initialize_fonts(c))
		return 0;

	return 1;
}


// Initialize the theme colors of the window.
static int x11_initialize_colors(Client *c)
{
	debug("Initializing colors...");

	struct ThemeColor* tc;
	for(tc = opt.colors; tc != NULL; tc = tc->hh.next)
	{
		XColor xcolor;
		if(XParseColor(display, colormap, tc->color, &xcolor) == BadColor)
		{
			fprintf(stderr, "Invalid X11 color %s.\n", tc->color);
			return 0;
		}
		XAllocColor(display, colormap, &xcolor);

		struct Color* new_color = malloc(sizeof(struct Color));
		strcpy(new_color->name, tc->name);
		new_color->pixel = xcolor.pixel;
		HASH_ADD_STR(c->colors, name, new_color);
	}
	return 1;
}


// Load XPM fonts
static int x11_initialize_fonts(Client* c)
{
	struct {
		char* font_name;
		XPM_Font* font;
	} fonts [] = {
		{ "led20", led20 },
		{ "led9", led9 },
		{ "led7", led7 },
		{ NULL, NULL },
	};

	debug("Initializing fonts...");

	int i, j;
	for(j=0; fonts[j].font_name; j++)
	{
		x11_new_font(c, fonts[j].font_name);
		for(i=0; fonts[j].font[i].xpm; i++)
		{
			Pixmap p = xpm_to_pixmap(fonts[j].font[i].xpm, 
					display, c);
			if(p)
				x11_font_char(c, fonts[j].font_name, 
						fonts[j].font[i].c, p);
			else
				fprintf(stderr, "warning: error creating "
						"character '%c' for the font "
						"%s.\n", fonts[j].font[i].c,
						fonts[j].font_name);
		}
	}
	return 1;
}


// Verify all windows for events. If there's any event, x11_do_events_client
// is called.
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


// On startup of the client, or when the user drags the mouse over the window,
// this function is called to calculate where the window should be moved to,
// and moves it.
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
	if(y < top_y)
		y = top_y;
	if(x > screen_w - 96)
		x = screen_w - 96;
	if(y > screen_h - 96)
		y = screen_h - 96;

	// check to see if it's on the attraction area
	int new_locked_column;
	if(x > screen_w - (96 * (max_column+2)) - opt.attract)
	{
		x = ((x - screen_w - 48) / 96) * 96 + screen_w;
		y = ((y+48) / 96) * 96 + top_y;
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


// Check window for events. If there's a mouse click, the event is sent to the
// client. If the user drags the mouse, x11_move_window is called.
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


// This is a very X11 specific function, that looks for the size of the
// upper dock (like a panel). This is necessary so that the dock doesn't
// get over the panel.
static int x11_panel_height(Window window)
{
	unsigned int height = 0;		// maximum height
	Window w;
	Window* children;
	unsigned int n_children;

	XQueryTree(display, window, &w, &w, &children, &n_children);
	
	// looks for each one of the children
	unsigned int i;
	for(i=0; i<n_children; i++)
	{
		// this is the property we're looking for
		Atom strut = XInternAtom(display, "_NET_WM_STRUT_PARTIAL", 
				False);
		Atom type_return;
		int actual_type;
		unsigned long nitems, bytes;
		unsigned char* data = NULL;
		
		// load window attributes (we only want to know about the
		//                         windows where y = 0)
		XWindowAttributes xwa;
		XGetWindowAttributes(display, window, &xwa);

		// load the property _NET_WM_STRUT_PARTIAL
		int s = XGetWindowProperty(display, window, strut, 0, LONG_MAX, 
				False, 
				XA_CARDINAL, &type_return, &actual_type,
				&nitems, &bytes, (unsigned char**)&data);
		if(s == Success)
		{
			Atom *state = (Atom *) data;
			// state[2] contains the "dock height"
			if(xwa.y == 0 && nitems > 0 && state[2])
				if(state[2] > height)
					height = state[2];
		}

		// recursively, traverse the tree of all children of children
		unsigned int children_max_height = x11_panel_height(children[i]);
		if(children_max_height > height)
			height = children_max_height;
	}

	return height;
}


// When the client disconnects, this function destroy the window.
void x11_destroy_client(Client* c)
{
	// free colors
	struct Color *color, *tmpc;
	HASH_ITER(hh, c->colors, color, tmpc)
	{
		HASH_DEL(c->colors, color);
		free(color);
	}

	// free images
	struct Image *image, *tmpi;
	HASH_ITER(hh, c->images, image, tmpi)
	{
		HASH_DEL(c->images, image);
		if(image->pixmap)
			XFreePixmap(display, image->pixmap);
		free(image);
	}
	
	// free fonts
	struct Font *font, *tmpf;
	HASH_ITER(hh, c->fonts, font, tmpf)
	{
		HASH_DEL(c->fonts, font);
		int i;
		for(i=0; i<255; i++)
			if(font->chr[i])
				XFreePixmap(display, font->chr[i]);
		free(font);
	}

	// destroy window
	XDestroyWindow(display, c->window);
	debug("Client window destroyed.");
}


// Close the connection with X.
void x11_quit()
{
	XCloseDisplay(display);
}
