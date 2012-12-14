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
		errx(1, "Invalid terrain type %d.", terrain);

found:;

	// find the most important tile around this one
	
	Terrain important = t_INVALID,
		nw = world_terrain(ui->world, x-1, y-1, NULL),
		n  = world_terrain(ui->world, x,   y-1, NULL),
		ne = world_terrain(ui->world, x+1, y-1, NULL),
		w  = world_terrain(ui->world, x-1, y,   NULL),
		e  = world_terrain(ui->world, x+1, y,   NULL),
		sw = world_terrain(ui->world, x-1, y+1, NULL),
		s  = world_terrain(ui->world, x,   y+1, NULL),
		se = world_terrain(ui->world, x+1, y+1, NULL),
		around[8] = { nw, n, ne, w, e, sw, s, se };
	for(i=0; i<8; i++)
		if(around[i] > terrain)
			important = imax(important, around[i]);
	if(important == t_OUT_OF_BOUNDS || important == t_INVALID)
		return;
	char* imp_img = NULL;
	i = -1;
	while(basic[++i].image)
		if(important == basic[i].terrain)
			imp_img = basic[i].image;
	if(!imp_img)
		errx(1, "Invalid terrain type %d", important);

	if(s == important && w == important)
		stack[st++] = res2(imp_img, "_ic_sw");
	else if(s == important)
		stack[st++] = res2(imp_img, "_ec_n");
	else 
	{
		if(se == important)
			stack[st++] = res2(imp_img, "_ec_nw");
		if(sw == important)
			stack[st++] = res2(imp_img, "_ec_ne");
	}
}
