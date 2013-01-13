#ifndef WORLD_CITY_H
#define WORLD_CITY_H

#include "util/point.h"

class City
{
public:
	City(Point pos, Biome const& biome)
		: pos(pos), biome(biome) { }

	Point const pos;
	Biome const& biome;
	std::vector<City const*> connections;
};

#endif
