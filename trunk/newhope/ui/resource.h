#ifndef RESOURCE_H
#define RESOURCE_H

#define BLACK       0
#define TRANSPARENT 1
#define WHITE       2

struct UI;
struct SDL_Surface;

int resources_load(struct UI*);
void resources_unload(struct UI*);

struct SDL_Surface* res(const char* name);

#endif
