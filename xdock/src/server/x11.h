#ifndef X11_H
#define X11_H

#include <X11/Xlib.h>

#define MAX_COLORS 16384

enum { BLACK, WHITE, PANEL_BG, PANEL_LT, PANEL_SW, UNLIT, LIT, BRIGHT, GLOW,
	WARNING };

typedef struct {
	Window window;
	GC gc;
	Pixmap pixmap;
	int locked_column;	/* if the window is locked in the right side
				   of the screen, this variable has the number
				   of the column (from right to left) */
	int color[MAX_COLORS];
	int n_colors;
} WM;

extern Display* display;

void x11_initialize();
int x11_setup_client(WM* wm);
void x11_do_events();
void x11_destroy_client(WM* wm);
void x11_quit();

#endif
