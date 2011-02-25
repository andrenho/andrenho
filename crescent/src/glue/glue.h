#ifndef GLUE_H
#define GLUE_H

#include <stdint.h>
#include <stdbool.h>

typedef struct {
	enum { TUNDRA=1, DESERT, PLAINS, PRAIRIE, STEPPE, MARSH, BOREAL_F, 
	       SCRUB, MIXED_F, SAVANNAH, WOODLAND, SWAMP, ARCTIC, SEA, OCEAN, 
	       HILLS, MOUNTAIN } terrain;
	bool special, river, road, plow;
	unsigned int rnd;
} Tile;

typedef struct {
	int w;
	int h;
	Tile* map;
} Game;

extern Game game;

int glue_init();
void glue_new_game(int w, int h);

#endif
