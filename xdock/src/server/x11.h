#ifndef X11_H
#define X11_H

#include <X11/Xlib.h>
#include <stdbool.h>

#include "structures.h"

extern Display* display;
extern Colormap colormap;

void x11_initialize();
int x11_setup_client(WM* wm);
void x11_do_events();
void x11_destroy_client(WM* wm);
void x11_quit();

#endif
