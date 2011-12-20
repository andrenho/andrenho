#include "keyboard.h"

#include <stdlib.h>
#include <curses.h>

Keyboard* keyboard_init(Memory *mem)
{
	Keyboard* keyboard = malloc(sizeof(Keyboard));
	keyboard->mem = mem;
	return keyboard;
}


void keyboard_step(Keyboard* keyboard, int* running, int* debugger)
{
	int c = getch();

	// no key pressed
	if(c == ERR)
		return;

	// quit
	if(c == 27) { *running = 0; return; }

	// debugger
	if(c == KEY_F(2)) { *debugger = 1; return; }
}
