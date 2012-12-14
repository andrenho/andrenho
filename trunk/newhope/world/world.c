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


Terrain world_terrain(World* world, int x, int y, int* special)
{
	srand(x + (y * world->w));
	if(special)
	{
		*special = rand() % 35;
		if(*special >= 4)
			*special = 0;
	}

	if(x == 2 && y == 2)
		return t_WATER;
	if((x == 5 || x == 6) && y == 2)
		return t_WATER;
	if((x == 2 || x == 3 || x == 4) && y == 5)
		return t_WATER;
	if((x == 7 || x == 9) && y == 5)
		return t_WATER;
	if((x == 2 && y == 8) || (x == 3 && y == 9))
		return t_WATER;

	if(x == 6 && y == 8)
		return t_WATER;
	if(x == 7 && y == 9)
		return t_DIRT;


	if(x < 0 || y < 0 || x >= world->w || y >= world->h)
		return t_OUT_OF_BOUNDS;
	else
		return t_GRASS;
}
