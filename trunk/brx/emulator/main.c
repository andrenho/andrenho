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
	curses_init();

	// load BIOS
	memory_load(mem, "bios.rom", 0xf000);

	// main loop
	int running = 1;
	while(running)
	{
		keyboard_step(kb, &running);
		cpu_step(cpu);
	}

	// end everything
	curses_end();

	return 0;
}
