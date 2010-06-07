#ifndef TILE_H
#define TILE_H

#include "structure.h"

class Tile
{
public:
	Tile() : ground(LAND), structure(0x0) { }

	enum { LAND, WATER } ground;
	int x, y;
	Structure* structure;
};

#endif
