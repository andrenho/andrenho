#include "world.h"

#include <stdlib.h>

#include "mapbuilding/mapbuild.h"
#include "util/log.h"

World* world_init(int w, int h)
{
	// initialize structure
	World* world = malloc(sizeof(World));
	world->w = w;
	world->h = h;

	// build map
	debug("Building map...");
	MapParameters pars = {
		.w = w,
		.h = h,
	};
	world->map = map_init(pars);
	debug("Map built.");

	return world;
}


void world_free(World* world)
{
	free(world);
}


TerrainSet world_terrain(World* world, int x, int y)
{
	TerrainSet ts;
	ts.topsoil = t_NOTHING;

	//srand(x + (y * world->w));
	ts.special = rand() % 100;
	if(ts.special >= 4)
		ts.special = 0;

	if(x < 0 || y < 0 || x >= world->w || y >= world->h)
		ts.biome = t_WATER;
	else
		ts.biome = t_DIRT;

	if(x < 3 || x >= (world->w - 3) || y < 3 || y >= (world->h - 3))
		ts.topsoil = t_WATER;

	return ts;
}
