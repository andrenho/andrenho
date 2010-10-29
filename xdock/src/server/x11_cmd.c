// TODO - check error messages

#include "x11_cmd.h"

#include <X11/Xlib.h>
#include <stdlib.h>
#include <stdio.h>

#include "network.h"
#include "x11_util.h"

#define ABS(x) ((x) < 0 ? -(x) : (x))


// Sets a new foreground color. It'll lookup in the hash if this color is already
// stored. If it isn't, calculates the pixel color (X11) and store in the hash.
// The `color` parameter can be a X11 color or a theme color.
static int x11_set_fg(Client* c, char* color)
{
	int pixel;
	struct Color* cl;

	HASH_FIND_STR(c->colors, color, cl);
	if(cl)
		pixel = cl->pixel;
	else
	{
		XColor xcolor;
		XParseColor(display, colormap, color, &xcolor); // TODO - check
		XAllocColor(display, colormap, &xcolor);
		pixel = xcolor.pixel;
	
		struct Color* new_color = malloc(sizeof(struct Color));
		strcpy(new_color->name, color);
		new_color->pixel = xcolor.pixel;
		HASH_ADD_STR(c->colors, name, new_color);
	}

	XSetForeground(display, c->gc, pixel);
	return 1;
}


// Draw a 3D carved panel.
int x11_panel(Client* c, int x, int y, int w, int h)
{
	if(x < 0 || y < 0 || x+w >= 96 || y+h >= 96 || w < 0 || h < 0)
		return 0;
	x11_set_fg(c, "panel_bg");
	XFillRectangle(display, c->pixmap, c->gc, x+1, y+1, w-1, h-1);

	XPoint shadow[] =  { { x, y+h-1 }, { x, y }, { x+w, y } },
	       light[] = { { x+w, y+1 }, { x+w, y+h }, { x, y+h } };
	x11_set_fg(c, "panel_lt");
	XDrawLines(display, c->pixmap, c->gc, light, 3, CoordModeOrigin);
	x11_set_fg(c, "panel_sw");
	XDrawLines(display, c->pixmap, c->gc, shadow, 3, CoordModeOrigin);
	return 1;
}


// Draw a pixel.
int x11_pixel(Client* c, char* color, int x, int y)
{
	if(x < 0 || y < 0 || x >= 96 || y >= 96)
		return 0;
	if(!x11_set_fg(c, color))
		return 0;
	XDrawPoint(display, c->pixmap, c->gc, x, y);
	return 1;
}


// Draw a line.
int x11_line(Client* c, char* color, int x1, int y1, int x2, int y2)
{
	if(x1 < 0 || y1 < 0 || x1 >= 96 || y1 >= 96
	|| x2 < 0 || y2 < 0 || x2 >= 96 || y2 >= 96)
		return 0;
	if(!x11_set_fg(c, color))
		return 0;
	XDrawLine(display, c->pixmap, c->gc, x1, y1, x2, y2);
	return 1;
}


// Draw a hollow rectangle.
int x11_rectangle(Client* c, char* color, int x, int y, int w, int h)
{
	if(x < 0 || y < 0 || x+w >= 96 || y+h >= 96 || w < 0 || h < 0)
		return 0;
	if(!x11_set_fg(c, color))
		return 0;
	XDrawLine(display, c->pixmap, c->gc, x, y, w, h);
	return 1;
}


// Draw a filled rectangle.
int x11_box(Client* c, char* color, int x, int y, int w, int h)
{
	if(x < 0 || y < 0 || x+w >= 96 || y+h >= 96 || w < 0 || h < 0)
		return 0;
	if(!x11_set_fg(c, color))
		return 0;
	XFillRectangle(display, c->pixmap, c->gc, x, y, w, h);
	return 1;
}


// Commit all changes made to the surface.
int x11_update(Client* c)
{
	XCopyArea(display, c->pixmap, c->window, c->gc, 0, 0, 96, 96, 0, 0);
	XFlush(display);
	return 1;
}


// Move a area in the image to a given direction, and fill the moved area with
// `bg_color`. It's useful for moving graphs.
int x11_movebox(Client* c, int x, int y, int w, int h, int move_x, int move_y,
		char* bg_color)
{
	if(x < 0 || y < 0 || x+w >= 96 || y+h >= 96 || w < 0 || h < 0)
		return 0;

	// move area
	XCopyArea(display, c->pixmap, c->pixmap, c->gc, x, y, w, h, 
			x+move_x, y+move_y);

	// draw background
	int bg_x, bg_y;
	if(!x11_set_fg(c, bg_color))
		return 0;
	if(move_x < 0)
		bg_x = x + w + move_x;
	else 
		bg_x = x + move_x;
	XFillRectangle(display, c->pixmap, c->gc, bg_x, y, ABS(move_x), h);

	if(move_y < 0)
		bg_y = y + h + move_y;
	else
		bg_y = y + move_y;
	XFillRectangle(display, c->pixmap, c->gc, x, bg_y, ABS(move_y), w);

	return 1;
}


// Send a XPM image to the server. The image can contain themed colors.
int x11_add_image(Client* c, char name[25], char** xpm)
{
	Pixmap pixmap = xpm_to_pixmap(xpm, display, c);
	if(!pixmap)
		return 0;

	struct Image* new_image = malloc(sizeof(struct Image));
	strncpy(new_image->name, name, 25);
	new_image->pixmap = pixmap;
	HASH_ADD_STR(c->images, name, new_image);
	return 1;
}


// Draw a image in the dock.
int x11_draw_image(Client* c, char* img, int x, int y)
{
	Window tmpw;
	int t;
	unsigned int w, h, ut;

	if(x < 0 || y < 0 || x >= 96 || y >= 96)
		return 0;

	struct Image* image;
	HASH_FIND_STR(c->images, img, image);
	if(!image)
	{
		fprintf(stderr, "From client %s: image %s doesn't exist in the "
				"server.\n", c->id, img);
		return 0;
	}
	XGetGeometry(display, c->pixmap, &tmpw, &t, &t,
			&w, &h, &ut, &ut);	
	XCopyArea(display, image->pixmap, c->pixmap, c->gc, 0, 0, w, h,
			x, y);
	return 1;
}


// Create a new font.
int x11_new_font(Client* c, char name[25])
{
	struct Font* font = malloc(sizeof(struct Font));
	strncpy(font->name, name, 25);
	int i;
	for(i=0; i<255; i++)
		font->chr[i] = 0;
	HASH_ADD_STR(c->fonts, name, font);
	return 1;
}


// Sets the image from a given char in the given font.
int x11_font_char(Client* c, char fontname[25], unsigned char ch, Pixmap p)
{
	struct Font* font;
	HASH_FIND_STR(c->fonts, fontname, font);
	if(!font)
	{
		fprintf(stderr, "On comand from %s: font %s not found.\n",
				c->id, fontname);
		return 0;
	}
	font->chr[ch] = p;
	return 1;
}


// Write a message on the dock.
int x11_print(Client* c, char fontname[25], int x, int y, unsigned char* text)
{
	struct Font* font;
	Window tmpw;
	int t;
	unsigned int w, h, ut;

	// get font
	HASH_FIND_STR(c->fonts, fontname, font);
	if(!font)
	if(!font)
	{
		fprintf(stderr, "On comand from %s: font %s not found.\n",
				c->id, fontname);
		return 0;
	}

	// print chars
	int i=0;
	while(text[i] != 0)
	{
		if(font->chr[text[i]] == 0)
		{
			fprintf(stderr, "On comand from %s: char '%c' not found "
					"on font %s\n", c->id, text[i], fontname);
		}
		else
		{
			XGetGeometry(display, font->chr[text[i]], &tmpw, &t, &t, 
					&w, &h, &ut, &ut);	
			XCopyArea(display, font->chr[text[i]], c->pixmap, c->gc, 
					0, 0, w, h, x, y);
			x += w;
		}
		i++;
	}

	return 1;
}


// When there is a event, send data to the client.
int x11_pointer_event(Client* c, char* type, int x, int y)
{
	net_send_client_data(c, "EVENT %s %d %d\n", type, x, y);
	return 1;
}
