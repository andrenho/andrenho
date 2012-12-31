#ifndef TERMINAL_H
#define TERMINAL_H

struct UI;
struct SDL_Surface;

enum TerminalState { OPEN, CLOSED, PARTIAL };

typedef struct Terminal {
	struct UI* ui;
	struct SDL_Surface* term_sf;
	enum TerminalState state;
	int y;
} Terminal;

Terminal* terminal_init(struct UI* ui);
void terminal_free(Terminal* terminal);

void terminal_state(Terminal* term, enum TerminalState state);
char terminal_getch(Terminal* term);

#endif
