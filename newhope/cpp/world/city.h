#ifndef WORLD_CITY_H
#define WORLD_CITY_H

#include "util/point.h"

class City
{
public:
	City(IPoint pos, Biome const& biome)
		: pos(pos), biome(biome) { }

	IPoint const pos;
	Biome const& biome;
	std::vector<City const*> connections;
};

#endif
