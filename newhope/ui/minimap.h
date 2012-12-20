#ifndef MINIMAP_H
#define MINIMAP_H

struct SDL_Surface;
struct UI;
struct World;

typedef struct Minimap {
	struct SDL_Surface* sf;
	int screen_w, screen_h;
} Minimap;

Minimap* minimap_init(struct World* world);
void minimap_free(Minimap* mm);

void minimap_display(Minimap* mm, struct UI* ui);

#endif
