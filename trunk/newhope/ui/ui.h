#ifndef UI_H
#define UI_H

#include <stdint.h>
#include "SDL.h"

typedef struct UI {
	int sdl_initialized;
	int active;
	SDL_Surface* screen;
	Uint32 ticks;
	int32_t rx, ry;
} UI;

UI* ui_init();
void ui_free(UI* ui);

void ui_draw(UI* ui);
void ui_moveview(UI* ui, int horiz, int vert);
void ui_start_frame(UI* ui);
void ui_end_frame(UI* ui);

#endif
