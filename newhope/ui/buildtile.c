#include "ui/buildtile.h"

#include "SDL.h"

#include "ui/resource.h"
#include "util/log.h"
#include "util/numbers.h"
#include "world/world.h"

static struct {
	Terrain terrain;
	char* image;
} basic[] = {
	{ t_GRASS,    "grass" },
	{ t_WATER,    "water" },
	{ t_DIRT,     "dirt"  },
	{ t_EARTH,    "earth" },
	{ t_LAVAROCK, "lavarock" },
	{ t_LAVA,     "lava"  },
	{ -1, NULL }
};


void build_tile(World* world, int x, int y, SDL_Surface* stack[MAX_STACK])
{
	int i;
	int st = 0;
	TerrainSet ts = world_terrain(world, x, y);
	
	// get basic image
	Terrain terrain = (ts.topsoil != t_NOTHING) ? ts.topsoil : ts.biome;
	i = 0;
	while(basic[i].image)
	{
		if(terrain == basic[i].terrain)
		{
			if(!ts.special)
				stack[st] = res(basic[i].image);
			else
			{
				char img[30];
				snprintf(img, 30, "%s_%d", basic[i].image,
						ts.special);
				stack[st] = res(img);
			}
			++st;
			goto found;
		}
		++i;
	}
	
	if(ts.biome != t_OUT_OF_BOUNDS) // TODO
		errx(1, "Invalid terrain type %d.", ts.biome);

found:;

	// find the most important tile around this one
	Terrain important = t_INVALID,
		nw = world_terrain(world, x-1, y-1).topsoil,
		n  = world_terrain(world, x,   y-1).topsoil,
		ne = world_terrain(world, x+1, y-1).topsoil,
		w  = world_terrain(world, x-1, y).topsoil,
		e  = world_terrain(world, x+1, y).topsoil,
		sw = world_terrain(world, x-1, y+1).topsoil,
		s  = world_terrain(world, x,   y+1).topsoil,
		se = world_terrain(world, x+1, y+1).topsoil,
		around[8] = { nw, n, ne, w, e, sw, s, se };
	for(i=0; i<8; i++)
		if(around[i] > ts.topsoil)
			important = imax(important, around[i]);
	if(important == t_OUT_OF_BOUNDS || important == t_INVALID 
			|| important == t_NOTHING)
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
	else if(s == important && e == important)
		stack[st++] = res2(imp_img, "_ic_se");
	else if(n == important && w == important)
		stack[st++] = res2(imp_img, "_ic_nw");
	else if(n == important && e == important)
		stack[st++] = res2(imp_img, "_ic_ne");
	else if(n == important || s == important || w == important 
	     || e == important)
	{
		if(n == important)
			stack[st++] = res2(imp_img, "_ec_s");
		if(s == important)
			stack[st++] = res2(imp_img, "_ec_n");
		if(e == important)
			stack[st++] = res2(imp_img, "_ec_w");
		if(w == important)
			stack[st++] = res2(imp_img, "_ec_e");
	}
	else if(se == important || sw == important)
	{
		if(se == important)
			stack[st++] = res2(imp_img, "_ec_nw");
		if(sw == important)
			stack[st++] = res2(imp_img, "_ec_ne");
	}
	else if(ne == important || nw == important)
	{
		if(ne == important)
			stack[st++] = res2(imp_img, "_ec_sw");
		if(nw == important)
			stack[st++] = res2(imp_img, "_ec_se");
	}
}
