#include "x11_cmd.h"

#include <X11/Xlib.h>

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
	XDrawLine(display, wm->pixmap, wm->gc, x, y, w, h);
	return 1;
}

int x11_update(WM* wm)
{
	XCopyArea(display, wm->pixmap, wm->window, wm->gc, 0, 0, 96, 96, 0, 0);
	XFlush(display);
	return 1;
}
