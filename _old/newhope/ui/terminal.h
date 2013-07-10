#ifndef TERMINAL_H
#define TERMINAL_H

struct UI;
struct SDL_Surface;
struct TTF_Font;

enum TerminalState { OPEN, CLOSED, PARTIAL };

#define LINES 13
#define COLS  42

typedef struct Terminal {
	struct UI* ui;
	struct SDL_Surface* term_sf;
	enum TerminalState state;
	int y;
	struct SDL_Surface *last_scr;
	int cur_x, cur_y;
	int font_w, font_h;
	struct SDL_Surface *fb_sf;
	char fb[COLS][LINES];
} Terminal;

Terminal* terminal_init(struct UI* ui);
void terminal_free(Terminal* terminal);

void terminal_draw(Terminal* term);
void terminal_state(Terminal* term, enum TerminalState state);
void terminal_printf(Terminal* term, char* fmt, ...);
char terminal_getch(Terminal* term);

#endif
