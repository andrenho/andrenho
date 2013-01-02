#include "world.h"

#include <stdlib.h>

#include "util/log.h"
#include "util/numbers.h"
#include "world/mapbuild.h"

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
		.seed = 1,
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
	
	// find special
	ts.special = rand() % 100;
	if(ts.special >= 4)
		ts.special = 0;

	// basic terrain (no polygon)
	if(x < 0 || y < 0 || x >= world->w || y >= world->h)
		ts.biome = t_WATER;
	else
		ts.biome = t_DIRT;

	// find biome polygon
	int bi;
	for(bi=0; bi<world->map->n_biomes; bi++)
	{
		int polySides = world->map->biomes[bi].n_points;
		float _x = x,
		      _y = y;
		float polyX[polySides],
		      polyY[polySides];
		int pi;
		for(pi=0; pi<polySides; pi++)
		{
			polyX[pi] = world->map->biomes[bi].polypt[pi].x;
			polyY[pi] = world->map->biomes[bi].polypt[pi].y;
		}
		if(point_in_polygon(polySides, polyX, polyY, _x, _y))
			ts.biome = t_GRASS;
	}

	return ts;
}
