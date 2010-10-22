#ifndef X11_H
#define X11_H

#include <X11/Xlib.h>

#define MAX_COLORS 16384

typedef struct {
	Window window;
	GC gc;
	Pixmap pixmap;
	int color[MAX_COLORS];
	int n_colors = 0;
} WM;

void x11_initialize();
int x11_setup_client(WM* wm);
void x11_do_events();
void x11_destroy_client(WM* wm);
void x11_quit();

// commands
int x11_panel(WM* wm, int x, int y, int w, int h);
int x11_update(WM* wm);

#endif
