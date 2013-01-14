#include "world/world.h"

#include <cstdlib>
#include <vector>

#include "util/logger.h"
#include "util/polygon.h"
#include "world/biome.h"

World::World(int w, int h) :
	w(w), h(h)
{
	logger.Debug("Building map...");
	MapParameters pars = {
		.seed = 1,
		.w = w,
		.h = h,
		.n_rivers = 12,
		.n_cities = 20,
		.n_roads = 10,
	};
	map = new MapBuild(pars);
	logger.Debug("Map built.");
}


World::~World()
{
	delete map;
}


TerrainType 
World::Terrain(int x, int y) const
{
	if((x == 2 && y == 2) || (x == 3 && y == 3))
		return t_GRASS;

	struct Point p = { x, y };
	for(auto const& biome : map->biomes)
		if(biome->polygon->PointInPolygon(p))
			return biome->terrain;
	return t_WATER;
}


int
World::Special(int x, int y) const
{
	int n = rand() % 100;
	if(n >= 4)
		return 0;
	else
		return n;
}
