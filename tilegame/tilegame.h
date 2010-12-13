#ifndef TILEGAME_H
#define TILEGAME_H

#include "SDL.h"

typedef struct {
	char* error;
	int layers;

	// private info
	const char* _filename;
	struct archive* _a;
} TileGame;

TileGame* TG_Init(const char* filename, char** error);
void TG_Quit(TileGame* tg);

#endif
