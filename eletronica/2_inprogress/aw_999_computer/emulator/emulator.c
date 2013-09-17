#include "display.h"
#include "ram.h"

Display* display;

int main()
{
	ram_init();
	display = display_init();

	while(display->active) {
		display_check_events(display);
		display_update(display);
	}
	
	return 0;
}
