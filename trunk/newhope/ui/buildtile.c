#include "ui/buildtile.h"

#include "SDL.h"

#include "ui/ui.h"
#include "ui/resource.h"
#include "util/log.h"
#include "util/numbers.h"
#include "world/world.h"

static struct {
	Terrain terrain;
	char* image;
} basic[] = {
	{ t_GRASS, "grass" },
	{ t_WATER, "water" },
	{ -1, NULL }
};

#define X (!0)
static struct {
	int tile[8];
	char* suffix;
} situation[] = {
	{ { 0, 0, 0,
	    0,    0,
	    0, 0, X }, "_ec_nw" },

	{ { 0, 0, 0,
	    0,    0,
	    0, X, 0 }, "_ec_n" },

	{ { 0, 0, 0,
	    0,    0,
	    X, 0, 0 }, "_ec_ne" },

	{ { 0, 0, 0,
	    0,    X,
	    0, 0, 0 }, "_ec_w" },

	{ { 0, 0, 0,
	    X,    0,
	    0, 0, 0 }, "_ec_e" },

	{ { 0, 0, X,
	    0,    0,
	    0, 0, 0 }, "_ec_sw" },

	{ { 0, X, 0,
	    0,    0,
	    0, 0, 0 }, "_ec_s" },

	{ { X, 0, 0,
	    0,    0,
	    0, 0, 0 }, "_ec_se" },

	{ { 0, 0, 0, 0, 0, 0, 0, 0 }, NULL }
};


void build_tile(UI* ui, int x, int y, SDL_Surface* stack[MAX_STACK])
{
	int st = 0;
	int special = 0;
	Terrain terrain = world_terrain(ui->world, x, y, &special);
	
	// get basic image
	int i = 0;
	while(basic[i].image)
	{
		if(terrain == basic[i].terrain)
		{
			if(!special)
				stack[st] = res(basic[i].image);
			else
			{
				char img[30];
				snprintf(img, 30, "%s_%d", basic[i].image,
						special);
				stack[st] = res(img);
			}
			++st;
			goto found;
		}
		++i;
	}
	
	if(terrain != t_OUT_OF_BOUNDS) // TODO
		errx(1, "Invalid terrain type.");

found:	;

	// find the most important tile around this one
	Terrain important = t_OUT_OF_BOUNDS,
		around[8] = {
			world_terrain(ui->world, x-1, y-1, NULL),
			world_terrain(ui->world, x,   y-1, NULL),
			world_terrain(ui->world, x+1, y-1, NULL),
			world_terrain(ui->world, x-1, y,   NULL),
			world_terrain(ui->world, x+1, y,   NULL),
			world_terrain(ui->world, x-1, y+1, NULL),
			world_terrain(ui->world, x,   y+1, NULL),
			world_terrain(ui->world, x+1, y+1, NULL)
		};
	for(i=0; i<8; i++)
		if(around[i] != terrain)
			important = imax(important, around[i]);
	
	// check the position of the most important tiles around
	i = 0;
	while(situation[i].suffix)
	{
		int j, match = 1;
		for(j=0; j<8; j++)
			if((around[j] == important && !situation[i].tile[j])
			|| (around[j] != important && situation[i].tile[j]))
			{
				match = 0;
				break;
			}
		// if matched, `i` is the situation value
		if(match)
		{
			char img[30];
			snprintf(img, 29, "%s%s", "water", // TODO
					situation[i].suffix);
			stack[st] = res(img);
			++st;
			break;
		}

		++i;
	}
}
