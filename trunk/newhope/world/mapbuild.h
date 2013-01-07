#ifndef MAPBUILD_H
#define MAPBUILD_H

#include "world.h"
#include "util/geometry.h"

typedef struct MapParameters {
	unsigned int seed;
	int w, h;
	int n_rivers;
} MapParameters;


typedef struct Biome {
	Polygon* polygon;
	Terrain terrain;
	int* pt_altitudes;
	int avg_altitude;
} Biome;


typedef struct Map {
	MapParameters* parameters;
	int n_biomes;
	Biome* biomes;
} Map;



Map* map_init(MapParameters map_pars);
void map_free(Map* map);

#endif
