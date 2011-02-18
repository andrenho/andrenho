#include "map.h"

#include <libtcod.h>

#include "gui.h"

void gui_draw_map()
{
}


void gui_do_map_events()
{
	TCOD_key_t key = TCOD_console_wait_for_keypress(true);
	switch(key.c)
	{
	case 'q':
		gui_state = QUIT;
		break;
	default:
		break;
	}
}
