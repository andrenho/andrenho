#include "debugger.h"

#include <stdlib.h>
#include <string.h>
#include <curses.h>

#include "cpu.h"
#include "ram.h"
extern CPU* cpu;

Debugger* debugger_init()
{
	Debugger* d = malloc(sizeof(Debugger));

	initscr();
	raw();
	noecho();
	refresh();
	curs_set(0);
	d->topPC = 0x1000;
	d->topRAM = 0x1000;

	return d;
}


void debugger_end()
{
	endwin();
}


static char* debug_register(uint8_t d)
{
	switch(d) {
	case 0x0: return "A";
	case 0x1: return "B";
	case 0x2: return "C";
	case 0x3: return "D";
	case 0x4: return "E";
	case 0x5: return "F";
	case 0x6: return "G";
	case 0x7: return "H";
	// TODO
	default: return "?";
	}
}


static int debugger_operation(Debugger* d, uint32_t pc, char* str)
{
	char *r1, *r2;
	uint32_t address;

	switch(ram_get(pc)) {
	case LD_ind16:
		r1 = debug_register(ram_get(pc+1) >> 4);
		r2 = debug_register(ram_get(pc+1) & 0xf);
		address = ram_get(pc+2) << 8;
		address |= ram_get(pc+3) & 0xff;
		sprintf(str, "ld %s, [%s+0x%04X]", r1, r2, address);
		return 4;
	case SET_imm8:
		r1 = debug_register(ram_get(pc+1) >> 4);
		address = ram_get(pc+2) & 0xff;
		sprintf(str, "st %s, 0x%02X", r1, address);
		return 3;
	case BZ_rel8:
		r1 = debug_register(ram_get(pc+1) >> 4);
		address = ram_get(pc+2) & 0xff;
		sprintf(str, "bz %s, 0x%02X", r1, address);
		return 3;
	case ST_dir16:
		r1 = debug_register(ram_get(pc+1) >> 4);
		address = ram_get(pc+2) << 8;
		address |= ram_get(pc+3) & 0xff;
		sprintf(str, "st [0x%02X], %s", address, r1);
		return 4;
	case INC_reg:
		r1 = debug_register(ram_get(pc+1) >> 4);
		sprintf(str, "inc %s", r1);
		return 2;
	case JMPb_rel8:
		address = ram_get(pc+1) & 0xff;
		sprintf(str, "jmpb 0x%02X", address);
		return 2;
	case HALT_imp:
		sprintf(str, "halt");
		return 1;
	default: strcpy(str, "INVALID"); return 1;
	}
}


void debugger_interact(Debugger* d)
{
	// instructions
	int y;
	uint32_t pc = d->topPC;
	for(y=0; y<(LINES - 9); y++) {
		static char str[30];
		int dif = debugger_operation(d, pc, str);
		mvprintw(y, 0, "  %06X:  %s               ", pc, str);
		if(pc == cpu->PC) {
			mvchgat(y, 0, 30, A_REVERSE, 1, NULL);
		}
		pc += dif;
	}

	// registers
	for(y=0; y<8; y++) {
		mvprintw(y, COLS-16, "%s: 0x%04X", debug_register(y),
			*cpu_find_register(cpu, y));
	}

	// separator line
	mvhline(LINES-9, 0, ACS_HLINE, COLS-1);

	// memory
	uint32_t m = d->topRAM;
	for(y=LINES-8; y<LINES; y++) {
		mvprintw(y, 0, "%06X :  %02X %02X %02X %02X %02X %02X %02X %02X  %02X %02X %02X %02X %02X %02X %02X %02X",
			m, ram_get(m), ram_get(m+1), ram_get(m+2), ram_get(m+3),
			ram_get(m+4), ram_get(m+5), ram_get(m+6), ram_get(m+7), ram_get(m+8),
			ram_get(m+9), ram_get(m+10), ram_get(m+11), ram_get(m+12), ram_get(m+13),
			ram_get(m+14), ram_get(m+15));
		m += 16;
	}

	// get keys
	int c = getch();
	switch(c)
	{
		case 'q':
			debugger_end();
			exit(1);
			break;
		case 's':
			cpu_step(cpu);
			break;
	}

	refresh();
}
