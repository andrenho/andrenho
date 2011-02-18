#include "gui.h"

#include <libtcod.h>

GUI_STATE gui_state;

int gui_init()
{
	TCOD_console_init_root(80, 50, "Fertile Crescent 0.1", false, 
			TCOD_RENDERER_SDL);
	return 1;
}
