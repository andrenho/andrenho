#include "debugger.h"

#include <stdlib.h>

Debugger* debugger_init(CPU* cpu, Memory *mem)
{
	Debugger* debugger = malloc(sizeof(Debugger));
	debugger->cpu = cpu;
	debugger->mem = mem;
	return debugger;
}


void debugger_load(Debugger* debugger, char* filename)
{
	
}


void debugger_run(Debugger* debugger)
{
	(void)debugger;

	
}
