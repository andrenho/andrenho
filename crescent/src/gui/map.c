#include "map.h"

#include <libtcod.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

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


static void get_terrain(int terrain, char* t1, char* t2, 
		TCOD_color_t* c1, TCOD_color_t* c2)
{
	if(terrain <= MARSH || terrain == ARCTIC)
		*t1 = *t2 = char_ground;
	else if(terrain == SCRUB)
	{
		*t1 = char_ground;
		*t2 = char_cactus;
	}
	else if(terrain <= SWAMP)
	{
		*t1 = char_ground;
		*t2 = char_forest;
	}
	else if(terrain == HILLS || terrain == MOUNTAIN)
	{
		*t1 = char_ground;
		*t2 = char_hills;
	}
	else if(terrain == SEA || terrain == OCEAN)
		*t1 = *t2 = char_sea;
	else
		assert(false);

	if(color)
	{
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

	int xx, yy;
	int terrain = game.map[x+y*game.w].terrain;

	// The edges of the terrain can be overlapped by other types of
	// terrain. As such, the image of the terrain is:
	//
	// AXB
	// XXX
	// CXD

	// get color & tile char
	TCOD_color_t c1_A, c1_B, c1_C, c1_D, c1_X,
		     c2_A, c2_B, c2_C, c2_D, c2_X;
	char t1_A, t1_B, t1_C, t1_D, t1_X,
	     t2_A, t2_B, t2_C, t2_D, t2_X;
	get_terrain(terrain, &t1_X, &t2_X, &c1_X, &c2_X);

	t1_A = t1_B = t1_C = t1_D = t1_X;
	t2_A = t2_B = t2_C = t2_D = t2_X;
	c1_A = c1_B = c1_C = c1_D = c1_X;
	c2_A = c2_B = c2_C = c2_D = c2_X;

	// find corners
	if(x > 1 && y > 1
	&& game.map[(x-1)+y*game.w].ovl < game.map[x+y*game.w].ovl
	&& game.map[x+(y-1)*game.w].ovl < game.map[x+y*game.w].ovl)
		get_terrain(game.map[(x-1)+y*game.w].terrain, &t1_A, &t2_A, &c1_A, &c2_A);

	if(x < game.w && y > 1
	&& game.map[(x+1)+y*game.w].ovl < game.map[x+y*game.w].ovl
	&& game.map[x+(y-1)*game.w].ovl < game.map[x+y*game.w].ovl)
		get_terrain(game.map[(x+1)+y*game.w].terrain, &t1_B, &t2_B, &c1_B, &c2_B);

	if(x > 1 && y < game.h
	&& game.map[(x-1)+y*game.w].ovl < game.map[x+y*game.w].ovl
	&& game.map[x+(y+1)*game.w].ovl < game.map[x+y*game.w].ovl)
		get_terrain(game.map[(x-1)+y*game.w].terrain, &t1_C, &t2_C, &c1_C, &c2_C);

	if(x < game.w && y < game.h
	&& game.map[(x+1)+y*game.w].ovl < game.map[x+y*game.w].ovl
	&& game.map[x+(y+1)*game.w].ovl < game.map[x+y*game.w].ovl)
		get_terrain(game.map[(x+1)+y*game.w].terrain, &t1_D, &t2_D, &c1_D, &c2_D);

	// draw tiles
	TCOD_console_set_default_background(NULL, 
			color ? TCOD_black : TCOD_white);
	for(xx=0; xx<3; xx++)
		for(yy=0; yy<3; yy++)
		{
			TCOD_color_t c1 = c1_X, c2 = c2_X;
			char t1 = t1_X, t2 = t2_X;
			if(xx==0 && yy==0) { t1=t1_A; t2=t2_A; c1=c1_A; c2=c2_A; }
			else if(xx==2 && yy==0) { t1=t1_B; t2=t2_B; c1=c1_B; c2=c2_B; }
			else if(xx==0 && yy==2) { t1=t1_C; t2=t2_C; c1=c1_C; c2=c2_C; }
			else if(xx==2 && yy==2) { t1=t1_D; t2=t2_D; c1=c1_D; c2=c2_D; }

			bool b = game.map[x+y*game.w].rnd & (1 << (yy*3+xx)) ? true : false;
			TCOD_console_put_char_ex(NULL, 
					(x+rx)*3+xx, (y+ry)*3+yy, 
					(b ? t1 : t2), (b ? c1 : c2), 
					color ? TCOD_black : TCOD_white);
		}
}


// Draw the user interface
void draw_interface()
{
	const int PANEL_H = 18,
	          MINIMAP_W = 18;

	TCOD_color_t fg = color ? TCOD_white : TCOD_lightest_grey;

	// borders
	TCOD_console_set_default_foreground(NULL, fg);
	TCOD_console_print_frame(NULL, 0, SCREEN_H-PANEL_H, SCREEN_W, PANEL_H, 
			PANEL_H, true, 0, NULL);
	TCOD_console_print_frame(NULL, 0, 0, SCREEN_W, SCREEN_H, false, 
			0, NULL);
	TCOD_console_set_char(NULL, 0, SCREEN_H-PANEL_H, TCOD_CHAR_TEEE);
	TCOD_console_set_char(NULL, SCREEN_W-1, SCREEN_H-PANEL_H, 
			TCOD_CHAR_TEEW);
	TCOD_console_set_char(NULL, SCREEN_W-MINIMAP_W, SCREEN_H-PANEL_H,
			TCOD_CHAR_TEES);
	TCOD_console_set_char(NULL, SCREEN_W-MINIMAP_W, SCREEN_H-1,
			TCOD_CHAR_TEEN);
	TCOD_console_vline(NULL, SCREEN_W-MINIMAP_W, SCREEN_H-PANEL_H+1, 
			PANEL_H-2, 0);

	// basic info
	//TCOD_console_print(NULL, 2, SCREEN_H-3, "Year: %d %s", 2000, "B.C.");
}


// Draw the map screen
void gui_draw_map()
{
	TCOD_console_clear(NULL);

	int x, y;
	for(x=MAX(rx, 1); x<=MAX(game.w+rx, SCREEN_W/3); x++)
		for(y=MAX(ry, 1); y<=MAX(game.h+ry, SCREEN_H/3); y++)
		{
			draw_tile(x, y);
			//draw_specials(x, y);
			// draw_unit(x, y);
			// draw_town(x, y);
		}

	draw_interface();

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
