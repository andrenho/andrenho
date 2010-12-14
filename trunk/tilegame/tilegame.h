#ifndef TILEGAME_H
#define TILEGAME_H

#include "SDL.h"
#include "uthash.h"

typedef struct {
	int id;
	char* image_file;
	int tile_w, tile_h;
	UT_hash_handle hh;
} Layer;

typedef struct {
	char* error;
	Layer* layers;
} TileGame;

TileGame* TG_Init(const char* filename, char** error);
void TG_Quit(TileGame* tg);

#endif
