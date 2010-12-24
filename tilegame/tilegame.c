#include "tilegame.h"

#include <stdlib.h>
#include <stdio.h>

#include "SDL_image.h"
#include "debug.h"

TG* 
TG_Init(SDL_Surface* screen, uint8_t tile_w, uint8_t tile_h)
{
	// check SDL initialized
	debug("Checking SDL...");
	if(!SDL_WasInit(SDL_INIT_VIDEO))
	{
		fprintf(stderr, "warning: SDL was not initialized.\n");
		return NULL;
	}

	// init SDL_image
	debug("Checking SDL_image...");
	if(!IMG_Init(IMG_INIT_PNG))
	{
		fprintf(stderr, "warning: Could not initialize SDL_image.\n");
		return NULL;
	}

	// create structure
	debug("Initializing TileGame structure.");
	TG* tg = malloc(sizeof(TG));
	tg->screen = screen;
	tg->tile_w = tile_w;
	tg->tile_h = tile_h;
	tg->images = NULL;
	tg->sdl_images = NULL;

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
	// free strcuture
	if(tg)
		free(tg);

	// close SDL_image

	return true;
}
