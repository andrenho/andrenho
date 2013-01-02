#ifndef MAPBUILD_H
#define MAPBUILD_H

#include "world.h"

typedef struct MapParameters {
	int w, h;
} MapParameters;



typedef struct Point {
	int x, y;
} Point;

typedef struct Biome {
	int n_points;
	Point* polypt;
	Terrain terrain;
} Biome;

typedef struct Map {
	MapParameters* parameters;
	int n_biomes;
	Biome* biomes;
} Map;



Map* map_init(MapParameters map_pars);
void map_free(Map* map);

#endif
