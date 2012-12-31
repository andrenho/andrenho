#ifndef TERMINAL_H
#define TERMINAL_H

struct UI;
struct SDL_Surface;
struct TTF_Font;

enum TerminalState { OPEN, CLOSED, PARTIAL };

typedef struct Terminal {
	struct UI* ui;
	struct SDL_Surface* term_sf;
	enum TerminalState state;
	int y;
	struct SDL_Surface *last_scr;
} Terminal;

Terminal* terminal_init(struct UI* ui);
void terminal_free(Terminal* terminal);

void terminal_draw(Terminal* term);
void terminal_state(Terminal* term, enum TerminalState state);
char terminal_getch(Terminal* term);

#endif
