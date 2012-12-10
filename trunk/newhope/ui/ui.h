#ifndef UI_H
#define UI_H

#include "SDL.h"

typedef struct UI {
	int sdl_initialized;
	int active;
	SDL_Surface* screen;
	Uint32 ticks;
} UI;

UI* ui_init();
void ui_free(UI* ui);

void ui_draw(UI* ui);
void ui_start_frame(UI* ui);
void ui_end_frame(UI* ui);

#endif
