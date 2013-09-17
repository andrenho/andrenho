#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdbool.h>
#include <stdint.h>
#include "SDL2/SDL.h"

typedef struct Display {
	SDL_Window* win;
	SDL_Renderer* ren;
	SDL_Texture *display, *px, *shadow;
	uint8_t cur_x, cur_y;
	bool active;
	bool data[84*48];
	bool charmap[64*96];
} Display;

#endif
