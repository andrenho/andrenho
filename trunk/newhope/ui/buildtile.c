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
	{ t_DIRT,  "dirt"  },
	{ -1, NULL }
};

static struct {
	int tile[8];
	char* suffix;
} situation[] = {
	{ { 2, 2, 2,
	    0,    0,
	    2, 1, 2 }, "_ec_n" },

	{ { 2, 1, 2,
	    0,    0,
	    2, 2, 2 }, "_ec_s" },

	{ { 2, 0, 2,
	    1,    2,
	    2, 0, 2 }, "_ec_e" },

	{ { 2, 0, 2,
	    2,    1,
	    2, 0, 2 }, "_ec_w" },
/*
	{ { 2, 2, 2,
	    2,    2,
	    2, 2, 1 }, "_ec_nw" },

	{ { 2, 2, 2,
	    2,    2,
	    1, 2, 2 }, "_ec_ne" },

	{ { 2, 2, 1,
	    2,    2,
	    2, 2, 2 }, "_ec_sw" },

	{ { 1, 2, 2,
	    2,    2,
	    2, 2, 2 }, "_ec_se" },

	{ { 2, 1, 2,
            1,    2,
	    2, 2, 2 }, "_ic_nw" },

	{ { 2, 2, 2,
            2,    1,
	    2, 1, 2 }, "_ic_se" },

	{ { 2, 2, 2,
            1,    2,
	    2, 1, 2 }, "_ic_sw" },

	{ { 2, 1, 2,
            2,    1,
	    2, 2, 2 }, "_ic_ne" },
*/
	{ { 0, 0, 0, 0, 0, 0, 0, 0 }, NULL }
};


void build_tile(UI* ui, int x, int y, SDL_Surface* stack[MAX_STACK])
{
	int i;
	int st = 0;
	int special = 0;
	Terrain terrain = world_terrain(ui->world, x, y, &special);
	
	// get basic image
	i = 0;
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

found:;

	// find the most important tile around this one
	Terrain important = t_INVALID,
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
			if(!((around[j] > terrain && situation[i].tile[j])
			  || (around[j] <= terrain && !situation[i].tile[j])
			  || situation[i].tile[j] == 2))

			{
				match = 0;
				break;
			}
		// if matched, `i` is the situation value
		if(match)
		{
			j = -1;
			while(basic[++j].image)
				if(important == basic[j].terrain)
				{
					char img[30];
					snprintf(img, 29, "%s%s", 
							basic[j].image,
							situation[i].suffix);
					if(x<ui->world->w && y<ui->world->h)
						debug("%d %d %s", x, y, img);
					stack[st] = res(img);
					++st;
					break;
				}
			//break;
		}

		++i;
	}
}
