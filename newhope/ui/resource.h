#ifndef RESOURCE_H
#define RESOURCE_H

#define BLACK       0
#define TRANSPARENT 1
#define WHITE       2

#define RES_CHARS 20

struct UI;
struct SDL_Surface;

int resources_load(struct UI*);
void resources_unload(struct UI*);

struct SDL_Surface* res(char name[RES_CHARS]);
struct SDL_Surface* res2(char *name1, char* name2);

#endif
