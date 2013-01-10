#ifndef BIOME_H
#define BIOME_H

#include "world/world.h"

class Polygon;

class Biome
{
public:
	Biome(Polygon* polygon);
	~Biome();

	Polygon* polygon;
	TerrainType terrain;
	int elevation;
	int moisture;
};

#endif
