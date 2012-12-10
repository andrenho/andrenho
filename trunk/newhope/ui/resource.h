#ifndef HASH_H
#define HASH_H

struct UI;
struct SDL_Surface;

int resources_load(struct UI*);
void resources_unload(struct UI*);

struct SDL_Surface* res(const char* name);

#endif
