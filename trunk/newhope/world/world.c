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
		.seed = 1,
		.w = w,
		.h = h,
		.n_rivers = 15,
	};
	world->map = map_init(pars);
	debug("Map built.");

	return world;
}


void world_free(World* world)
{
	map_free(world->map);
	free(world);
}


TerrainSet world_terrain(World* world, int x, int y)
{
	TerrainSet ts;

	//srand(x + (y * world->w));
	
	// find special
	ts.special = rand() % 100;
	if(ts.special >= 4)
		ts.special = 0;

	// basic terrain (no polygon)
	ts.biome = t_WATER;

	// find biome polygon
	int bi;
	for(bi=0; bi<world->map->n_biomes; bi++)
	{
		// prefilter the polygons
		if(x < world->map->biomes[bi].polygon->limit_x1
		|| y < world->map->biomes[bi].polygon->limit_y1
		|| x > world->map->biomes[bi].polygon->limit_x2
		|| y > world->map->biomes[bi].polygon->limit_y2)
			continue;

		// check if point is on the polygon
		Point p = { x, y };
		if(point_in_polygon(p, world->map->biomes[bi].polygon))
			ts.biome = world->map->biomes[bi].terrain;
	}

	return ts;
}
