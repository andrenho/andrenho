#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <curses.h>

#include "fcca.h"


FCCA* F = NULL;


int main (void) 
{
	F = fcca_init();
	new_game(F, 10, 10);

	// initialize curses
	initscr();
	
	getch();

	// finalize curses
	endwin();

	// finalize lua
	fcca_close(fcca);

	return 0;
}
