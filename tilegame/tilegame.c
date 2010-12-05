#include "tilegame.h"

TG* TG_Init(int tile_w, int tile_h)
{
	TG* tg = malloc(sizeof(TG));
	tg->x = x;
	tg->y = y;
	return tg;
}


void TG_SetChar(TG* tg, unsigned char c, SDL_Surface* sf)
{
}


SDL_Surface* TG_SetVideoMode(TG* tg, int w, int h, int bpp, Uint32 flags)
{
	return SDL_SetVideoMode(tg->w * w, tg->h * h, bpp, flags);
}
