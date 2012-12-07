#ifndef UI_H
#define UI_H

typedef struct UI {
	int sdl_initialized;
} UI;

UI* ui_init();
void ui_free(UI* ui);

#endif
