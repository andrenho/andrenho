#include "world.h"

#include <stdlib.h>

World* world_init(int w, int h)
{
	World* world = malloc(sizeof(World));
	world->w = w;
	world->h = h;
	return world;
}


void world_free(World* world)
{
	free(world);
}


Terrain world_terrain(World* world, int x, int y)
{
	if(x < 0 || y < 0 || x >= world->w || y >= world->h)
		return t_OUT_OF_BOUNDS;
	else
		return t_GRASS;
}
