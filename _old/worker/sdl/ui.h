#ifndef UI_H
#define UI_H

#include "SDL.h"
#include "level.h"

typedef struct {
	enum { EDIT, RUN } state;
	int active;
	Level* lv;
	SDL_Surface* scr;
} UI;

UI* ui_init();
void ui_init_level(UI* ui, Level* lv);
void ui_draw(UI* ui);
void ui_edit(UI* ui);
void ui_step(UI* ui);
void ui_free(UI** ui);

#endif
