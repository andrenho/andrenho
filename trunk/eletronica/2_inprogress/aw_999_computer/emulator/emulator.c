#include "display.h"
#include "ram.h"
#include "cpu.h"
#include "debugger.h"

#include <string.h>
#include <getopt.h>

Display* display;
CPU* cpu;
Debugger* dbg = NULL;

int main(int argc, char* argv[])
{
	// initialize components
	ram_init();
	cpu = cpu_init();
	display = display_init();

	// check arguments
	int c;
	while((c = getopt(argc, argv, "d")) != -1) {
		switch(c) {
		case 'd':
			dbg = debugger_init(); break;
		}
	}
	if(optind < argc) {
		ram_load_rom(0x1000, argv[optind]);
	}

	// main loop
	int i;
	while(display->active) {
		display_check_events(display);
		display_update(display);

		if(dbg) {
			debugger_interact(dbg);
		} else {
			for(i=0; i<256; i++) {
				if(cpu_step(cpu)) {
					goto next;
				}
			}
		}
next: {}
	}

	// finalize
	if(dbg) {
		debugger_end();
	}
	
	return 0;
}
