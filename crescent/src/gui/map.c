#include "map.h"

#include <libtcod.h>
#include <assert.h>

#include "gui.h"
#include "glue.h"

#ifndef MIN
#  define MIN(x,y) ((x)>(y) ? (x) : (y))
#endif
#ifndef MAX
#  define MAX(x,y) ((x)>(y) ? (x) : (y))
#endif

static int rx = -1, ry = -1; // relative map position

// Setup map
void gui_map_init()
{
	TCOD_console_set_background_flag(NULL, TCOD_BKGND_SET);
	TCOD_console_set_default_background(NULL, TCOD_black);
	TCOD_console_set_default_foreground(NULL, TCOD_white);
	TCOD_console_clear(NULL);
}


static void draw_tile(int x, int y)
{
	assert(x >= 0 && y >= 0 && x < game.w && y < game.h);

	int i;

	TCOD_console_set_default_background(NULL, TCOD_black);
	switch(game.map[x+y*game.w].terrain)
	{
	case OCEAN:
		TCOD_console_set_default_foreground(NULL, TCOD_dark_blue);
		for(i=0; i<3; i++)
			TCOD_console_print(NULL, (x+rx)*3, (y+ry)*3+i, "~~~");
		break;
	case SEA:
		TCOD_console_set_default_foreground(NULL, TCOD_light_blue);
		for(i=0; i<3; i++)
			TCOD_console_print(NULL, (x+rx)*3, (y+ry)*3+i, "~~~");
		break;
	case PLAINS:
		TCOD_console_set_default_foreground(NULL, TCOD_dark_green);
		for(i=0; i<3; i++)
			TCOD_console_print(NULL, (x+rx)*3, (y+ry)*3+i, ",,,");
		break;
	default:
		break;
	}
}


// Draw the map screen
void gui_draw_map()
{
	TCOD_console_clear(NULL);

	int x, y;
	for(x=MAX(rx, 0); x<MAX(game.w+rx, SCREEN_W/3); x++)
		for(y=MAX(ry, 0); y<MAX(game.h+ry, SCREEN_H/3); y++)
			draw_tile(x, y);
	TCOD_console_flush();
}


// Parse map events
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
