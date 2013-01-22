#ifndef WORLD_CITY_H
#define WORLD_CITY_H

#include "util/defines.h"
#include "util/point.h"

class City {
public:
	City(IPoint pos, Biome const& biome)
		: pos(pos), biome(biome) { }

	IPoint const pos;
	Biome const& biome;
	std::vector<const City*> connections;

private:
	DISALLOW_COPY_AND_ASSIGN(City);
};

#endif
