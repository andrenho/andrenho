#ifndef TILEGAME_H
#define TILEGAME_H

#include <stdint.h>
#include <stdbool.h>

#include "SDL.h"

#include "uthash.h"

typedef struct {
	uint32_t id;
	SDL_Surface* image;
	uint32_t x, y;
	UT_hash_handle hh;
} TG_Image;

typedef struct {
	char* filename;
	SDL_Surface* sf;
	UT_hash_handle hh;
} TG_SDL_Image;

typedef struct {
	SDL_Surface* screen;
	uint8_t tile_w, tile_h;
	TG_SDL_Image* sdl_images;
//	TG_Image* images;
} TG;

TG* TG_Init(SDL_Surface* screen, uint8_t tile_w, uint8_t tile_h);
uint32_t TG_LoadImage(TG* tg, const char* filename, uint32_t x, uint32_t y);
bool TG_BlitImage(TG* tg, uint32_t img, int32_t x, int32_t y, 
		int8_t fine_x, int8_t fine_y);
bool TG_End(TG* tg);

#endif
