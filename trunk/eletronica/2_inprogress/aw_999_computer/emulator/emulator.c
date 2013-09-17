#include "display.h"
#include "ram.h"
#include "cpu.h"

Display* display;
CPU* cpu;

int main(int argc, char* argv[])
{
	ram_init();
	if(argc > 1) {
		ram_load_rom(0x1000, argv[argc-1]);
	}
	cpu = cpu_init();
	display = display_init();

	int i;
	while(display->active) {
		for(i=0; i<256; i++) {
			if(cpu_step(cpu)) {
				goto next;
			}
		}
next:
		display_check_events(display);
		display_update(display);
	}
	
	return 0;
}
