#include "gui.h"

#include <libtcod.h>

GUI_STATE gui_state;
bool color = false;


// Initialize main window
int gui_init()
{
	TCOD_console_init_root(SCREEN_W, SCREEN_H, "Fertile Crescent 0.1", 
			false, TCOD_RENDERER_GLSL);

	TCOD_console_set_default_background(NULL, color ? TCOD_black : TCOD_white);
	TCOD_console_set_default_foreground(NULL, color ? TCOD_white : TCOD_white);
	TCOD_console_clear(NULL);
	
	return 1;
}
