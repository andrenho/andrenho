#include <stdio.h>

#include "curses_.h"
#include "cpu.h"
#include "video.h"
#include "memory.h"
#include "keyboard.h"
#include "debugger.h"

int main(int argc, char* argv[])
{
	// initialize everything
	Memory *mem = memory_init(1024);
	CPU* cpu = cpu_init(mem);
	Keyboard* kb = keyboard_init(mem);
	Debugger *dbg = debugger_init(cpu, mem);
	curses_init();

	// load BIOS
	memory_load(mem, "bios.rom", 0xf000);
	debugger_load(dbg, "bios.debug");

	// main loop
	int running = 1;
	int debugger = 1;
	while(running)
	{
		keyboard_step(kb, &running, &debugger);
		if(debugger)
			debugger_run(dbg);
		cpu_step(cpu);
	}

	// end everything
	curses_end();

	return 0;
}
