#include "cpu.h"

#include <stdlib.h>
#include <stdio.h>

#define GET(x) get(cpu->mem, (x))

CPU* cpu_init(Memory *mem)
{
	CPU* cpu = malloc(sizeof(CPU));
	cpu->mem = mem;
	cpu->p = 0xf000;
	return cpu;
}


void cpu_step(CPU* cpu)
{
	int sz;

	// get parameters
	switch(GET(cpu->p) >> 1)
	{
		// type D
		case 0x3C: 
			sz = 1;
			break;
		default:
			fprintf(stderr, "Invalid opcode 0x%02X in 0x%08X.\n", 
					GET(cpu->p), cpu->p);
			exit(1);
			break;
	}

	// execute opcode
	switch(GET(cpu->p) >> 1)
	{
		// nop
		case 0x3C:
			break;
		default:
			abort();
	}

	// advance P
	cpu->p += sz;
}
