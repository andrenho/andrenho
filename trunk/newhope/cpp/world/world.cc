#include "world/world.h"

#include <cstdlib>

#include "util/logger.h"

World::World(int w, int h) :
	w(w), h(h)
{
	logger.Debug("Building map...");
	MapParameters pars = {
		.seed = 1,
		.w = w,
		.h = h,
		.n_rivers = 15,
		.n_cities = 25,
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
	return t_WATER;
}


bool 
World::Special(int x, int y) const
{
	return !(rand() % 100 >= 4);
}
