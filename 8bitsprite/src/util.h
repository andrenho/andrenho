#ifndef UTIL_H
#define UTIL_H

#include <stdarg.h>

#include "SDL.h"
#include "SDL_ttf.h"

#define BLACK         0
#define WHITE       254
#define TRANSPARENT 255

extern SDL_Surface* screen;
extern TTF_Font* font;

// print a string on the screen
int print(int x, int y, char* fmt, ...);

// draw a list of buttons and return the coordinates
SDL_Rect* draw_buttons(char* fmt, ...);

#endif
