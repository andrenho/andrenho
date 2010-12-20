#include "tilegame.h"

#include <stdlib.h>

TG* 
TG_Init(SDL_Surface* screen, uint8_t tile_w, uint8_t tile_h)
{
	TG* tg = malloc(sizeof(TG));
	tg->screen = screen;
	tg->tile_w = tile_w;
	tg->tile_h = tile_h;

	return tg;
}


uint32_t 
TG_LoadImage(TG* tg, const char* filename, uint32_t x, uint32_t y)
{
	return 0;
}


bool 
TG_BlitImage(TG* tg, uint32_t img, int32_t x, int32_t y, 
		int8_t fine_x, int8_t fine_y)
{
	return false;
}


bool 
TG_End(TG* tg)
{
	return false;
}
