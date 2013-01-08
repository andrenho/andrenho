#ifndef MAPBUILD_H
#define MAPBUILD_H

#include "world.h"
#include "util/geometry.h"

struct PointHash;


typedef struct PointList {
	int n;
	Point* points;
} PointList;

typedef struct MapParameters {
	unsigned int seed;
	int w, h;
	int n_rivers;
} MapParameters;


typedef struct Biome {
	Polygon* polygon;
	Terrain terrain;
	int avg_altitude;
	int moisture;
} Biome;


typedef struct Map {
	MapParameters* parameters;
	int n_biomes;
	Biome* biomes;
	struct PointHash* pt_altitudes;
	struct PointHash* neighbours;
	int n_rivers;
	PointList* rivers;
} Map;



Map* map_init(MapParameters map_pars);
void map_free(Map* map);

#endif
