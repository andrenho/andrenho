#ifndef DEBUGGER_H
#define DEBUGGER_H

#include <stdint.h>

typedef struct Debugger {
	uint32_t topPC;
} Debugger;

Debugger* debugger_init();
void debugger_interact(Debugger* d);
void debugger_end();

#endif
