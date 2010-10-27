#ifndef X11_CMD_H
#define X11_CMD_H

#include "x11.h"

// TODO - always use unsigned

// commands
int x11_panel(WM* wm, int x, int y, int w, int h);
int x11_pixel(WM* wm, char* color, int x, int y);
int x11_line(WM* wm, char* color, int x1, int y1, int x2, int y2);
int x11_rectangle(WM* wm, char* color, int x1, int x2, int y1, int y2);
int x11_box(WM* wm, char* color, int x1, int x2, int y1, int y2);
int x11_movebox(WM* wm, int x, int y, int w, int h, int move_x, int move_y,
		char* bg_color);
int x11_update(WM* wm);

// images
int x11_add_image(WM* wm, char name[25], char** xpm, int themed);
int x11_draw_image(WM* wm, char* img, int x, int y);

// text
int x11_new_font(WM* wm, char name[25]);
int x11_font_char(WM* wm, char font[25], unsigned char c, Pixmap p);
int x11_print(WM* wm, char font[25], int x, int y, unsigned char* text);

#endif
