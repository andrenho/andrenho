#ifndef RESOURCE_H
#define RESOURCE_H

#define BLACK       0
#define TRANSPARENT 1
#define WHITE       2

#define RES_CHARS 20

struct UI;
struct SDL_Surface;

// names:
//   TYPE_0      - regular full tile
//   TYPE_n      - special full tile
//   TYPE_IC_dir - internal corner
//   TYPE_EC_dir - external corner
//   TYPE_S_n    - small

int resources_load(struct UI*);
void resources_unload(struct UI*);

struct SDL_Surface* res(char name[RES_CHARS]);

#endif
