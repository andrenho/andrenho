#ifndef UTIL_H
#define UTIL_H

#include <stdarg.h>

#include "SDL.h"
#include "SDL_ttf.h"

#define BLACK         0
#define WHITE       254
#define GRAY        255
#define TRANSPARENT 255

#define P(sf,x,y) (*((Uint8 *)(sf)->pixels + (y) * (sf)->pitch + (x)))

extern SDL_Surface* screen;
extern TTF_Font* font;

// print a string on the screen
int print(int x, int y, char* fmt, ...);

// question the user
int ask_yn(char* question);

// draw a list of buttons and return the coordinates
SDL_Rect* draw_buttons(char* fmt, ...);

/*
inline Uint8 get(SDL_Surface *sf, int x, int y);
inline void set(SDL_Surface *sf, int x, int y, Uint8 color);
*/

#endif
