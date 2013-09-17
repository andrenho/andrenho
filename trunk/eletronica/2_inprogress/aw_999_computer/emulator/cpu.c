#include "cpu.h"

#include <stdlib.h>
#include <stdio.h>

#include "ram.h"

CPU* cpu_init()
{
	CPU* c = malloc(sizeof(CPU));
	c->PC = 0x1000;
	return c;
}


static uint16_t* cpu_find_register(CPU* c, uint8_t d)
{
	switch(d) {
	case 0x0: return &c->A;
	case 0x1: return &c->B;
	case 0x2: return &c->C;
	case 0x3: return &c->D;
	case 0x4: return &c->E;
	case 0x5: return &c->F;
	case 0x6: return &c->G;
	case 0x7: return &c->H;
	// TODO
	default:
		  fprintf(stderr, "Invalid register 0x%X in 0x%X.\n", d, c->PC);
		  exit(1);
	}
}


bool cpu_step(CPU* c)
{
	uint16_t *r1, *r2;
	uint16_t address;
	uint8_t opc = ram_get(c->PC++);

	switch(opc) {
	case LD_imm8:
		break;
	case LD_ind16:
		r1 = cpu_find_register(c, ram_get(c->PC) >> 4);
		r2 = cpu_find_register(c, ram_get(c->PC++) & 0xf);
		address = ram_get(c->PC++) << 8;
		address += ram_get(c->PC++) & 0xf;
		*r1 = ram_get(*r2 + address);
		break;
	case SET_imm8:
		r1 = cpu_find_register(c, ram_get(c->PC++) >> 4);
		*r1 = ram_get(c->PC++);
		break;
	case BZ_rel8:
		r1 = cpu_find_register(c, ram_get(c->PC++) >> 4);
		address = ram_get(c->PC++) & 0xf;
		if(*r1 == 0) {
			c->PC += ((int8_t)address) - 1;
		}
		break;
	case ST_dir16:
		r1 = cpu_find_register(c, ram_get(c->PC) >> 4);
		r2 = cpu_find_register(c, ram_get(c->PC++) & 0xf);
		address = ram_get(c->PC++) << 8;
		address += ram_get(c->PC++) & 0xf;
		ram_set(address+(*r1), *r2);
		break;
	case INC_reg:
		r1 = cpu_find_register(c, ram_get(c->PC++) >> 4);
		(*r1)++;
		break;
	case JMPb_rel8:
		address = ram_get(c->PC++) & 0xf;
		c->PC -= (address + 1);
		break;
	case HALT_imp:
		// TODO
		break;
	default:
		fprintf(stderr, "Invalid opcode 0x%X in 0x%X.\n", opc, c->PC--);
		exit(1);
	}
	return false;
}
