// TODO - check error messages

#include "x11_cmd.h"

#include <X11/Xlib.h>

#include "x11_xpm.h"

#define ABS(x) ((x) < 0 ? -(x) : (x))


int x11_panel(WM* wm, int x, int y, int w, int h)
{
	if(x < 0 || y < 0 || x+w >= 96 || y+h >= 96 || w < 0 || h < 0)
		return 0;
	XSetForeground(display, wm->gc, wm->color[PANEL_BG]);
	XFillRectangle(display, wm->pixmap, wm->gc, x+1, y+1, w-1, h-1);

	XPoint shadow[] =  { { x, y+h-1 }, { x, y }, { x+w, y } },
	       light[] = { { x+w, y+1 }, { x+w, y+h }, { x, y+h } };
	XSetForeground(display, wm->gc, wm->color[PANEL_LT]);
	XDrawLines(display, wm->pixmap, wm->gc, light, 3, CoordModeOrigin);
	XSetForeground(display, wm->gc, wm->color[PANEL_SW]);
	XDrawLines(display, wm->pixmap, wm->gc, shadow, 3, CoordModeOrigin);
	return 1;
}


int x11_pixel(WM* wm, int color, int x, int y)
{
	if(x < 0 || y < 0 || x >= 96 || y >= 96)
		return 0;
	if(color >= wm->n_colors)
		return 0;
	XSetForeground(display, wm->gc, wm->color[color]);
	XDrawPoint(display, wm->pixmap, wm->gc, x, y);
	return 1;
}


int x11_line(WM* wm, int color, int x1, int y1, int x2, int y2)
{
	if(x1 < 0 || y1 < 0 || x1 >= 96 || y1 >= 96
	|| x2 < 0 || y2 < 0 || x2 >= 96 || y2 >= 96)
		return 0;
	if(color >= wm->n_colors)
		return 0;
	XSetForeground(display, wm->gc, wm->color[color]);
	XDrawLine(display, wm->pixmap, wm->gc, x1, y1, x2, y2);
	return 1;
}


int x11_rectangle(WM* wm, int color, int x, int y, int w, int h)
{
	if(x < 0 || y < 0 || x+w >= 96 || y+h >= 96 || w < 0 || h < 0)
		return 0;
	if(color >= wm->n_colors)
		return 0;
	XSetForeground(display, wm->gc, wm->color[color]);
	XDrawLine(display, wm->pixmap, wm->gc, x, y, w, h);
	return 1;
}


int x11_box(WM* wm, int color, int x, int y, int w, int h)
{
	if(x < 0 || y < 0 || x+w >= 96 || y+h >= 96 || w < 0 || h < 0)
		return 0;
	if(color >= wm->n_colors)
		return 0;
	XSetForeground(display, wm->gc, wm->color[color]);
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
		int bg_color)
{
	if(x < 0 || y < 0 || x+w >= 96 || y+h >= 96 || w < 0 || h < 0)
		return 0;
	if(bg_color >= wm->n_colors)
		return 0;

	// move area
	XCopyArea(display, wm->pixmap, wm->pixmap, wm->gc, x, y, w, h, 
			x+move_x, y+move_y);

	// draw background
	int bg_x, bg_y;
	XSetForeground(display, wm->gc, wm->color[bg_color]);
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


int x11_add_image(WM* wm, char** xpm, int themed)
{
	(void) themed; // TODO
	Pixmap pixmap = xpm_to_pixmap(xpm, display, wm->window);
	free_xpm(xpm);
	wm->image[wm->n_images++] = pixmap;
	return wm->n_images-1;
}


int x11_draw_image(WM* wm, int image, int x, int y)
{
	Window tmpw;
	int t;
	unsigned int w, h, ut;

	if(x < 0 || y < 0 || x >= 96 || y >= 96)
		return 0;
	if(image >= wm->n_images)
		return 0;

	XGetGeometry(display, wm->pixmap, &tmpw, &t, &t,
			&w, &h, &ut, &ut);	
	XCopyArea(display, wm->image[image], wm->pixmap, wm->gc, 0, 0, w, h,
			x, y);
	return 1;
}
