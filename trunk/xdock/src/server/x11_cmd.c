// TODO - check error messages

#include "x11_cmd.h"

#include <X11/Xlib.h>
#include <stdlib.h>

#include "network.h"
#include "x11_util.h"

#define ABS(x) ((x) < 0 ? -(x) : (x))


static int x11_set_fg(WM* wm, char* color)
{
	int pixel;
	struct Color* c;

	HASH_FIND_STR(wm->colors, color, c);
	if(c)
		pixel = c->pixel;
	else
	{
		XColor xcolor;
		XParseColor(display, colormap, color, &xcolor); // TODO - check
		XAllocColor(display, colormap, &xcolor);
		pixel = xcolor.pixel;
	
		struct Color* new_color = malloc(sizeof(struct Color));
		strcpy(new_color->name, color);
		new_color->pixel = xcolor.pixel;
		HASH_ADD_STR(wm->colors, name, new_color);
	}

	XSetForeground(display, wm->gc, pixel);
	return 1;
}


int x11_panel(WM* wm, int x, int y, int w, int h)
{
	if(x < 0 || y < 0 || x+w >= 96 || y+h >= 96 || w < 0 || h < 0)
		return 0;
	x11_set_fg(wm, "panel_bg");
	XFillRectangle(display, wm->pixmap, wm->gc, x+1, y+1, w-1, h-1);

	XPoint shadow[] =  { { x, y+h-1 }, { x, y }, { x+w, y } },
	       light[] = { { x+w, y+1 }, { x+w, y+h }, { x, y+h } };
	x11_set_fg(wm, "panel_lt");
	XDrawLines(display, wm->pixmap, wm->gc, light, 3, CoordModeOrigin);
	x11_set_fg(wm, "panel_sw");
	XDrawLines(display, wm->pixmap, wm->gc, shadow, 3, CoordModeOrigin);
	return 1;
}


int x11_pixel(WM* wm, char* color, int x, int y)
{
	if(x < 0 || y < 0 || x >= 96 || y >= 96)
		return 0;
	if(!x11_set_fg(wm, color))
		return 0;
	XDrawPoint(display, wm->pixmap, wm->gc, x, y);
	return 1;
}


int x11_line(WM* wm, char* color, int x1, int y1, int x2, int y2)
{
	if(x1 < 0 || y1 < 0 || x1 >= 96 || y1 >= 96
	|| x2 < 0 || y2 < 0 || x2 >= 96 || y2 >= 96)
		return 0;
	if(!x11_set_fg(wm, color))
		return 0;
	XDrawLine(display, wm->pixmap, wm->gc, x1, y1, x2, y2);
	return 1;
}


int x11_rectangle(WM* wm, char* color, int x, int y, int w, int h)
{
	if(x < 0 || y < 0 || x+w >= 96 || y+h >= 96 || w < 0 || h < 0)
		return 0;
	if(!x11_set_fg(wm, color))
		return 0;
	XDrawLine(display, wm->pixmap, wm->gc, x, y, w, h);
	return 1;
}


int x11_box(WM* wm, char* color, int x, int y, int w, int h)
{
	if(x < 0 || y < 0 || x+w >= 96 || y+h >= 96 || w < 0 || h < 0)
		return 0;
	if(!x11_set_fg(wm, color))
		return 0;
	XFillRectangle(display, wm->pixmap, wm->gc, x, y, w, h);
	return 1;
}


int x11_update(WM* wm)
{
	XCopyArea(display, wm->pixmap, wm->window, wm->gc, 0, 0, 96, 96, 0, 0);
	XFlush(display);
	return 1;
}


int x11_movebox(WM* wm, int x, int y, int w, int h, int move_x, int move_y,
		char* bg_color)
{
	if(x < 0 || y < 0 || x+w >= 96 || y+h >= 96 || w < 0 || h < 0)
		return 0;

	// move area
	XCopyArea(display, wm->pixmap, wm->pixmap, wm->gc, x, y, w, h, 
			x+move_x, y+move_y);

	// draw background
	int bg_x, bg_y;
	if(!x11_set_fg(wm, bg_color))
		return 0;
	if(move_x < 0)
		bg_x = x + w + move_x;
	else 
		bg_x = x + move_x;
	XFillRectangle(display, wm->pixmap, wm->gc, bg_x, y, ABS(move_x), h);

	if(move_y < 0)
		bg_y = y + h + move_y;
	else
		bg_y = y + move_y;
	XFillRectangle(display, wm->pixmap, wm->gc, x, bg_y, ABS(move_y), w);

	return 1;
}


int x11_add_image(WM* wm, char name[25], char** xpm, int themed)
{
	(void) themed; // TODO

	Pixmap pixmap = xpm_to_pixmap(xpm, display, wm);
	free_xpm(xpm);

	struct Image* new_image = malloc(sizeof(struct Image));
	strncpy(new_image->name, name, 25);
	new_image->pixmap = pixmap;
	HASH_ADD_STR(wm->images, name, new_image);
	return 1;
}


int x11_draw_image(WM* wm, char* img, int x, int y)
{
	Window tmpw;
	int t;
	unsigned int w, h, ut;

	if(x < 0 || y < 0 || x >= 96 || y >= 96)
		return 0;

	struct Image* image;
	HASH_FIND_STR(wm->images, img, image);
	if(!image)
		return 0; // TODO - display error

	XGetGeometry(display, wm->pixmap, &tmpw, &t, &t,
			&w, &h, &ut, &ut);	
	XCopyArea(display, image->pixmap, wm->pixmap, wm->gc, 0, 0, w, h,
			x, y);
	return 1;
}


int x11_new_font(WM* wm, char name[25])
{
	struct Font* font = malloc(sizeof(struct Font));
	strncpy(font->name, name, 25);
	int i;
	for(i=0; i<255; i++)
		font->chr[i] = 0;
	HASH_ADD_STR(wm->fonts, name, font);
	return 1;
}


int x11_font_char(WM* wm, char fontname[25], unsigned char c, Pixmap p)
{
	struct Font* font;
	HASH_FIND_STR(wm->fonts, fontname, font);
	if(!font)
		return 0; // TODO
	font->chr[c] = p;
	// TODO - what if a char doesn't exist?
	return 1;
}


int x11_print(WM* wm, char fontname[25], int x, int y, unsigned char* text)
{
	struct Font* font;
	Window tmpw;
	int t;
	unsigned int w, h, ut;

	// get font
	HASH_FIND_STR(wm->fonts, fontname, font);
	if(!font)
		return 0; // TODO

	// print chars
	int i=0;
	while(text[i] != 0)
	{
		XGetGeometry(display, font->chr[text[i]], &tmpw, &t, &t, &w, &h, 
				&ut, &ut);	
		XCopyArea(display, font->chr[text[i]], wm->pixmap, wm->gc, 
				0, 0, w, h, x, y);
		x += w;
		i++;
	}

	return 1;
}

int x11_pointer_event(Client* c, char* type, int x, int y)
{
	net_send_client_data(&c->net, "EVENT %s %d %d\n", type, x, y);
	return 1;
}
