#ifndef CPU_H
#define CPU_H

#include "memory.h"

#include <stdint.h>

typedef struct {
	Memory *mem;
	uint32_t p;
} CPU;

CPU* cpu_init(Memory *mem);
void cpu_step(CPU* cpu);

#endif
