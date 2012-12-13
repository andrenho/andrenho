#ifndef DRAWTILE_H
#define DRAWTILE_H

#define MAX_STACK 10

struct SDL_Surface;
struct UI;

void build_tile(struct UI* ui, int x, int y, 
		struct SDL_Surface* stack[MAX_STACK]);

#endif
