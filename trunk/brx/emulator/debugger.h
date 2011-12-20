#ifndef DEBUGGER_H
#define DEBUGGER_H

#include "cpu.h"
#include "memory.h"

typedef struct {
	CPU *cpu;
	Memory *mem;
} Debugger;

Debugger* debugger_init(CPU* cpu, Memory *mem);
void debugger_load(Debugger* debugger, char* filename);
void debugger_run(Debugger* debugger);

#endif

