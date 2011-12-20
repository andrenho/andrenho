#ifndef CPU_H
#define CPU_H

#include "memory.h"

typedef struct {
	Memory *mem;
} CPU;

CPU* cpu_init(Memory *mem);
void cpu_step(CPU* cpu);

#endif
