#ifndef WORLD_H
#define WORLD_H

// the order is the importance
typedef enum {
	t_INVALID       = -1,
	t_OUT_OF_BOUNDS	= 0,
	t_WATER		= 1,
	t_GRASS		= 2,
	t_DIRT          = 3,
} Terrain;

typedef struct World {
	int w, h;
} World;

World* world_init(int w, int h);
void world_free(World* world);

Terrain world_terrain(World* world, int x, int y, int* special);

#endif
