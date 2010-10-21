#ifndef X11_XPM_H
#define X11_XPM_H

#include <X11/Xlib.h>

char** square_xpm(long color);
void free_xpm(char** xpm);
Pixmap xpm_to_pixmap(char* xpm[], Display* display, Window window);

#endif
