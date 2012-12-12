#ifndef RESOURCE_H
#define RESOURCE_H

#define BLACK       0
#define TRANSPARENT 1
#define WHITE       2

struct UI;
struct SDL_Surface;

// names:
//   TYPE_0      - regular full tile
//   TYPE_n      - special full tile
//   TYPE_IC_dir - internal corner
//   TYPE_EC_dir - external corner
//   TYPE_S_n    - small
typedef enum Resource {

	NOTHING=0, 

	GRASS_0, GRASS_1, GRASS_2, GRASS_3,
	GRASS_IC_NW, GRASS_IC_SW, GRASS_IC_NE, GRASS_IC_NE,
	GRASS_EC_NW, GRASS_EC_SW, GRASS_EC_NE, GRASS_EC_NE,
	GRASS_EC_N, GRASS_EC_S, GRASS_EC_E, GRASS_EC_W,
	GRASS_S_0, GRASS_S_1,
	
} Resource;

int resources_load(struct UI*);
void resources_unload(struct UI*);

struct SDL_Surface* res(Resource name);

#endif
