#ifndef WORLD_CITY_H
#define WORLD_CITY_H

#include "util/defines.h"
#include "util/point.h"

class Biome;

class City {
public:
	City(Point<int> pos, const Biome& biome)
		: pos(pos), biome(biome) { }

	const Point<int> pos;
	const Biome& biome;
	std::vector<const City*> connections;

private:
	DISALLOW_COPY_AND_ASSIGN(City);
};

#endif
