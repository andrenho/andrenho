#ifndef MAPBUILD_H
#define MAPBUILD_H

#include "world.h"
#include "util/geometry.h"

typedef struct MapParameters {
	int w, h;
	unsigned int seed;
} MapParameters;


typedef struct Biome {
	Polygon* polygon;
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
