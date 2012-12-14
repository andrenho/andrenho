#ifndef UI_H
#define UI_H

#include <stdint.h>
#include "SDL.h"

struct World;
struct TerrainSurface;

typedef struct UI {
	int sdl_initialized;
	int active;
	SDL_Surface* screen;
	Uint32 ticks;
	int32_t rx, ry;
	struct World* world;
	int flip_next_frame;
	struct TerrainSurface* trsurf;
} UI;

UI* ui_init(struct World* world);
void ui_free(UI* ui);

void ui_draw(UI* ui);
void ui_moveview(UI* ui, int horiz, int vert);
void ui_start_frame(UI* ui);
void ui_end_frame(UI* ui);

#endif
