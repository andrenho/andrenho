#ifndef TERMINAL_H
#define TERMINAL_H

struct UI;
struct SDL_Surface;

typedef struct Terminal {
	struct UI* ui;
	struct SDL_Surface* term_sf;
} Terminal;

Terminal* terminal_init(struct UI* ui);
void terminal_free(Terminal* terminal);

#endif
