#ifndef X11_CMD_H
#define X11_CMD_H

#include "x11.h"

// commands
int x11_panel(WM* wm, int x, int y, int w, int h);
int x11_pixel(WM* wm, int color, int x, int y);
int x11_line(WM* wm, int color, int x1, int y1, int x2, int y2);
int x11_rectangle(WM* wm, int color, int x1, int x2, int y1, int y2);
int x11_box(WM* wm, int color, int x1, int x2, int y1, int y2);
int x11_movebox(WM* wm, int x, int y, int w, int h, int move_x, int move_y,
		int bg_color);
int x11_update(WM* wm);
int x11_add_image(WM* wm, char** xpm, int themed);

#endif
