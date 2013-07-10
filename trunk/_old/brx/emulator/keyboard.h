#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "memory.h"

typedef struct {
	Memory *mem;
} Keyboard;

Keyboard* keyboard_init(Memory *mem);
void keyboard_step(Keyboard* keyboard, int* running, int* debugger);

#endif
