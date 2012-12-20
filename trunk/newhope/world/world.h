#ifndef WORLD_H
#define WORLD_H

// the order is the importance
typedef enum {
	t_INVALID       = -1,
	t_OUT_OF_BOUNDS	= 0,
	t_NOTHING       = 1,
	t_WATER		= 99,
	t_LAVA          = 98,
	t_SNOW          = 80,
	t_GRASS		= 50,
	t_DIRT          = 20,
	t_EARTH,
	t_LAVAROCK,
} Terrain;

typedef struct {
	Terrain biome;
	Terrain topsoil;
	int special;
} TerrainSet;

typedef struct World {
	int w, h;
} World;

World* world_init(int w, int h);
void world_free(World* world);

TerrainSet world_terrain(World* world, int x, int y);

#endif
