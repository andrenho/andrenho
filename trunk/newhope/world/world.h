#ifndef WORLD_H
#define WORLD_H

typedef enum {
	t_OUT_OF_BOUNDS,
	t_GRASS,
} Terrain;

typedef struct World {
	int w, h;
} World;

World* world_init(int w, int h);
void world_free(World* world);

Terrain world_terrain(World* world, int x, int y);

#endif
