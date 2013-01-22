#ifndef BIOME_H
#define BIOME_H

#include "world/world.h"

class Polygon;

class Biome {
public:
	Biome(Polygon* polygon)
		: polygon(polygon), terrain(t_DIRT), elevation(0), moisture(0),
		  has_city(false) {}
	~Biome() { delete polygon; }

	Polygon* polygon;
	TerrainType terrain;
	int elevation;
	int moisture;
	bool has_city;
};

#endif
