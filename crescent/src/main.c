#include "gui.h"
#include "map.h"
#include "glue.h"

int main(int argc, char* argv[])
{
	(void)argc, (void)argv;

	// initialize everything
	if(!gui_init())
		return 1;
	if(!glue_init())
		return 1;

	// initialize game
	glue_new_game(50, 50);
	gui_map_init();

	// main loop
	while(gui_state != QUIT)
	{
		switch(gui_state)
		{
			case MAP:
				gui_draw_map();
				gui_do_map_events();
				break;
			default:
				break;
		}
	}

	return 0;
}
