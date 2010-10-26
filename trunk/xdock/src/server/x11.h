#ifndef X11_H
#define X11_H

#include <X11/Xlib.h>
#include <stdbool.h>

#include "uthash.h"

struct Color {
	char name[25];
	int pixel;
	UT_hash_handle hh;
};

struct Image {
	char name[25];
	Pixmap pixmap;
	UT_hash_handle hh;
};

struct Font {
	char name[25];
	Pixmap chr[255];
	UT_hash_handle hh;
};

typedef struct {
	Window window;
	GC gc;
	Pixmap pixmap;
	int locked_column;	/* if the window is locked in the right side
				   of the screen, this variable has the number
				   of the column (from right to left) */
	struct Color* colors;
	struct Image* images;
	struct Font* fonts;
} WM;

extern Display* display;
extern Colormap colormap;

void x11_initialize();
int x11_setup_client(WM* wm);
void x11_do_events();
void x11_destroy_client(WM* wm);
void x11_quit();

#endif
