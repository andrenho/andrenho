#ifndef MAPBUILD_H
#define MAPBUILD_H

#include "world.h"
#include "util/geometry.h"

#define LAVA_POINTS 5

struct PointHash;
struct City;


typedef struct PointList {
	int n;
	Point* points;
} PointList;

typedef struct MapParameters {
	unsigned int seed;
	int w, h;
	int n_rivers;
	int n_cities;
	int n_roads;
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
	Point lava[LAVA_POINTS];
	int n_cities;
	struct City** cities;
	int n_roads;
	PointList* roads;
} Map;



Map* map_init(MapParameters map_pars);
void map_free(Map* map);

#endif
