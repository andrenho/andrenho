#ifndef WORLD_WORLD_H
#define WORLD_WORLD_H

#include "world/mapbuild.h"

// the order is the importance
typedef enum {
	t_INVALID       = -1,
	t_OUT_OF_BOUNDS	= 0,
	t_NOTHING       = 1,
	t_WATER		= 99,
	t_LAVA          = 98,
	t_SNOW          = 80,
	t_GRASS		= 50,
	t_DIRT          = 20,
	t_EARTH,
	t_LAVAROCK,
	t_ROCK,
	t_TUNDRA,
	t_HOTFOREST,
	t_COLDFOREST,
} TerrainType;

class World {
public:
	World(int w, int h);
	~World();

	TerrainType Terrain(int x, int y) const;
	int Special(int x, int y) const;

	const int w, h;
	const MapBuild* map;
};

#endif
