#include "gui.h"

#include <libtcod.h>

GUI_STATE gui_state;
bool color = false;


// Initialize main window
int gui_init()
{
	TCOD_console_init_root(SCREEN_W, SCREEN_H, "Fertile Crescent 0.1", 
			false, TCOD_RENDERER_SDL);
	return 1;
}
