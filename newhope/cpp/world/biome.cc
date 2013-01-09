#include "world/biome.h"

#include "util/polygon.h"

Biome::Biome(Polygon* polygon)
	: polygon(polygon), terrain(t_DIRT), altitude(0), moisture(0)
{
}

Biome::~Biome()
{
	delete polygon;
}
