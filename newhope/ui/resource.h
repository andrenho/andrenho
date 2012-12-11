#ifndef RESOURCE_H
#define RESOURCE_H

#define BLACK       0
#define TRANSPARENT 1
#define WHITE       2

struct UI;
struct SDL_Surface;

typedef enum Resource {
	NOTHING=0, GRASSM,
} Resource;

int resources_load(struct UI*);
void resources_unload(struct UI*);

struct SDL_Surface* res(Resource name);

#endif
