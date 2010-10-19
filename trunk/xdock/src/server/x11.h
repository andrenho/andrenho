#ifndef X11_H
#define X11_H

#include <X11/Xlib.h>

typedef struct {
	Window* window;
} WM;

void x11_initialize();
int x11_setup_client(WM* wm);
void x11_destroy_client(WM* wm);
void x11_quit();

// commands
int x11_draw_panel(WM* wm, int x1, int x2, int y1, int y2);

#endif
