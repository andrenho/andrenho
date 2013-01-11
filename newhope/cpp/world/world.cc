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
		.seed = 4,
		.w = w,
		.h = h,
		.n_rivers = 12,
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
	struct Point p = { x, y };
	for(std::vector<Biome*>::const_iterator biome = map->biomes.begin();
			biome != map->biomes.end(); biome++)
		if((*biome)->polygon->PointInPolygon(p))
			return (*biome)->terrain;
	return t_WATER;
}


bool 
World::Special(int x, int y) const
{
	return !(rand() % 100 >= 4);
}
