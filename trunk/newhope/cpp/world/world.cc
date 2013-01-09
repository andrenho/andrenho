#include "world/world.h"

#include <cstdlib>

#include "util/logger.h"

World::World(int w, int h) :
	w(w), h(h)
{
	logger.Debug("Building map...");
	
	// TODO
	
	logger.Debug("Map built.");
}


World::~World()
{
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
