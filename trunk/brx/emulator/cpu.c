#include "cpu.h"

#include <stdlib.h>

CPU* cpu_init(Memory *mem)
{
	CPU* cpu = malloc(sizeof(CPU));
	cpu->mem = mem;
	return cpu;
}


void cpu_step(CPU* cpu)
{
	(void) cpu;
}
