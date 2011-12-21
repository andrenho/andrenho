#include "curses_.h"

#include <curses.h>

void curses_init()
{
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	timeout(0);
	curs_set(0);
	refresh();
}


void curses_end()
{
	endwin();
}
