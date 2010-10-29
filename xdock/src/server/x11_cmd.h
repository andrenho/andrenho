#ifndef X11_CMD_H
#define X11_CMD_H

#include "client.h"
#include "x11.h"

// commands
int x11_panel(Client* c, int x, int y, int w, int h);
int x11_pixel(Client* c, char* color, int x, int y);
int x11_line(Client* c, char* color, int x1, int y1, int x2, int y2);
int x11_rectangle(Client* c, char* color, int x1, int x2, int y1, int y2);
int x11_box(Client* c, char* color, int x1, int x2, int y1, int y2);
int x11_movebox(Client* c, int x, int y, int w, int h, int move_x, int move_y,
		char* bg_color);
int x11_update(Client* c);

// images
int x11_add_image(Client* c, char name[25], char** xpm);
int x11_draw_image(Client* c, char* img, int x, int y);

// text
int x11_new_font(Client* c, char name[25]);
int x11_font_char(Client* c, char font[25], unsigned char ch, Pixmap p);
int x11_print(Client* c, char font[25], int x, int y, unsigned char* text);

// events
int x11_pointer_event(Client* c, char* type, int x, int y);

#endif
