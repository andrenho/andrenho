#ifndef SDL_H
#define SDL_H

#include "SDL.h"

int inside(int x, int y, SDL_Rect r);
void intersect(SDL_Rect* r, SDL_Rect r2);
void intersect_scr(SDL_Rect* r);
void draw_line(SDL_Surface* sf, int x0, int y0, int x1, int y1, int w, Uint32 c);

#endif
