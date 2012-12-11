#include "world.h"

#include <stdlib.h>

World* world_init()
{
	World* world = malloc(sizeof(World));
	return world;
}


void world_free(World* world)
{
	free(world);
}
