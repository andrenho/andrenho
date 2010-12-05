#ifndef TILEGAME_H
#define TILEGAME_H

#include "SDL.h"

typedef struct {
	int w, h;
} TG;

TG* TG_Init(int tile_w, int tile_h);
void TG_SetChar(TG* tg, unsigned char c, SDL_Surface* sf);
SDL_Surface* TG_SetVideoMode(TG* tg, int w, int h, int bpp, Uint32 flags);

#endif
