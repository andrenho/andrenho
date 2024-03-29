#ifndef CPU_H
#define CPU_H

#include <stdbool.h>
#include <stdint.h>

typedef struct CPU {
	uint16_t A, B, C, D, E, F, G, H;
	uint32_t ST, PC;
	bool halt_mode;
} CPU;

CPU* cpu_init();
bool cpu_step(CPU* cpu);
uint16_t* cpu_find_register(CPU* c, uint8_t d);

#define LD_imm8 	0x01
#define LD_ind16	0x06
#define BZ_rel8		0x83
#define SET_imm8 	0x10
#define ST_dir16	0x0D
#define INC_reg		0x41
#define JMPb_rel8	0x4C
#define HALT_imp	0xFF

#endif
