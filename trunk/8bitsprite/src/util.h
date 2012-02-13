#ifndef UTIL_H
#define UTIL_H

#include <stdarg.h>

#include "SDL.h"
#include "SDL_ttf.h"

extern SDL_Surface* screen;
extern TTF_Font* font;

int print(int x, int y, char* fmt, ...);

#endif
