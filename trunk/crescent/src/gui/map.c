#include "map.h"

#include <libtcod.h>
#include <assert.h>
#include <stdlib.h>

#include "gui.h"
#include "glue.h"

#ifndef MIN
#  define MIN(x,y) ((x)>(y) ? (x) : (y))
#endif
#ifndef MAX
#  define MAX(x,y) ((x)>(y) ? (x) : (y))
#endif

static int rx = -1, ry = -1; // relative map position

// tile characters
static char char_ground = '.',
	    char_sea = '~',
	    char_forest = '*', //TCOD_CHAR_CLUB,
	    char_hills = 0x1e,
	    char_cactus = 0xc4;

// tile colors
static TCOD_color_t *tile_color;

// Initialize everything and setup map
void gui_map_init()
{
	TCOD_console_set_background_flag(NULL, TCOD_BKGND_SET);
	TCOD_console_set_default_background(NULL, color ? TCOD_black : TCOD_white);
	TCOD_console_set_default_foreground(NULL, color ? TCOD_white : TCOD_white);
	TCOD_console_clear(NULL);

	TCOD_color_t tc[] = {
		TCOD_black,

		TCOD_cyan, 		// tundra
		TCOD_light_amber,	// desert
		TCOD_dark_green,	// plains
		TCOD_light_green,	// prairie
		TCOD_light_orange,	// steppe
		TCOD_dark_grey,		// marsh

		// color of the trees
		TCOD_darkest_green,	// boreal forest
		TCOD_green,		// scrub forest
		TCOD_dark_green,	// mixed forest
		TCOD_light_green,	// savaannah
		TCOD_light_orange,	// woodland
		TCOD_dark_grey,		// swamp

		// other
		TCOD_white,		// arctic (and mountaintops)
		TCOD_light_blue,	// sea
		TCOD_dark_blue,		// ocean
		TCOD_darker_red,	// hills
		TCOD_dark_grey		// montain ground 
	};
	tile_color = malloc(sizeof(tc));
	memcpy(tile_color, tc, sizeof(tc));
}


static void get_tile_color(int x, int y, TCOD_color_t* c1, TCOD_color_t* c2)
{
	if(color)
	{
		int terrain = game.map[x+y*game.w].terrain;
		if(terrain <= MARSH || (terrain >= ARCTIC && terrain <= HILLS))
			*c1 = *c2 = tile_color[terrain];
		else if(terrain >= BOREAL_F && terrain <= SWAMP)
		{
			*c1 = tile_color[terrain - 6];
			*c2 = tile_color[terrain];
		}
		else if(terrain == MOUNTAIN)
		{
			*c1 = tile_color[MOUNTAIN];
			*c2 = tile_color[ARCTIC];
		}
		else
			assert(false);
	}
	else
	{
		*c1 = TCOD_lightest_grey;
		*c2 = TCOD_lightest_grey;
	}
}


static void draw_tile(int x, int y)
{
	assert(x >= 1 && y >= 1 && x <= game.w && y <= game.h);

	int i, xx, yy;

	// setup colors
	TCOD_color_t c1, c2;
	TCOD_console_set_default_background(NULL, color ? TCOD_black : TCOD_white);
	get_tile_color(x, y, &c1, &c2);

	// setup tiles
	char t1, t2;
	int terrain = game.map[x+y*game.w].terrain;
	if(terrain <= MARSH || terrain == ARCTIC)
		t1 = t2 = char_ground;
	else if(terrain == SCRUB)
	{
		t1 = char_ground;
		t2 = char_cactus;
	}
	else if(terrain <= SWAMP)
	{
		t1 = char_ground;
		t2 = char_forest;
	}
	else if(terrain == HILLS || terrain == MOUNTAIN)
	{
		t1 = char_ground;
		t2 = char_hills;
	}
	else if(terrain == SEA || terrain == OCEAN)
		t1 = t2 = char_sea;
	else
	{
		printf("%d %d %d\n", x, y, terrain);
		assert(false);
	}

	// draw tiles
	for(xx=0; xx<3; xx++)
		for(yy=0; yy<3; yy++)
		{
			bool b = game.map[x+y*game.w].rnd & (1 << (yy*3+xx)) ? true : false;
			TCOD_console_put_char_ex(NULL, (x+rx)*3+xx, (y+ry)*3+yy, 
					(b ? t1 : t2), (b ? c1 : c2), color ? TCOD_black : TCOD_white);
		}
}


// Draw the map screen
void gui_draw_map()
{
	TCOD_console_clear(NULL);

	int x, y;
	for(x=MAX(rx, 1); x<=MAX(game.w+rx, SCREEN_W/3); x++)
		for(y=MAX(ry, 1); y<=MAX(game.h+ry, SCREEN_H/3); y++)
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
