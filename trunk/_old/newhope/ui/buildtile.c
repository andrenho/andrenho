#include "ui/buildtile.h"

#include <stdlib.h>
#include "SDL.h"

#include "ui/resource.h"
#include "util/log.h"
#include "util/numbers.h"
#include "world/world.h"

static struct {
	Terrain terrain;
	char* image;
} basic[] = {
	{ t_GRASS,    "grass"    },
	{ t_WATER,    "water"    },
	{ t_DIRT,     "dirt"     },
	{ t_EARTH,    "earth"    },
	{ t_LAVAROCK, "lavarock" },
	{ t_LAVA,     "lava"     },
	{ t_SNOW,     "snow"     },
	{ -1, NULL }
};


typedef struct {
	Terrain nw, n, ne, w, e, sw, s, se;
} Borders;


static void build_tile_find_borders(World* world, int x, int y, 
		SDL_Surface* stack[MAX_STACK], int st, Terrain here);
static void build_tile_add_borders(World* world, int x, int y, 
		SDL_Surface* stack[MAX_STACK], int* st, Borders b, Terrain t, 
		char* imp_img);


void build_tile(World* world, int x, int y, SDL_Surface* stack[MAX_STACK])
{
	int i;
	int st = 0;
	TerrainSet ts = world_terrain(world, x, y);
	
	// get basic image
	Terrain terrain = ts.biome;
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

found:
	build_tile_find_borders(world, x, y, stack, st, terrain);
}


static void build_tile_find_borders(World* world, int x, int y, 
		SDL_Surface* stack[MAX_STACK], int st, Terrain here)
{
	// find other terrains around this one
	int _x, _y;
	Terrain t[8] = { [0 ... 7] = t_INVALID };
	int i = 0;
	for(_x=x-1; _x<=x+1; _x++)
		for(_y=y-1; _y<=y+1; _y++)
			if(!(_x==x && _y==y))
			{
				Terrain tr = world_terrain(world, _x, _y).biome;
				if(tr > here)
					t[i] = tr;
				i++;
			}

	// order array
	int cmp(const void *a, const void *b) 
	{ 
		const int *da = (const int*)a;
		const int *db = (const int*)b;
		return *da - *db; 
	}
	qsort(t, 8, sizeof(Terrain), &cmp);

	// for each terrain found, do
	for(i=0; i<8; i++)
	{
		if(t[i] <= t_NOTHING)
			continue;

		// find tiles around
		Borders b = {
			world_terrain(world, x-1, y-1).biome == t[i] ? t[i] : t_NOTHING,
			world_terrain(world, x,   y-1).biome == t[i] ? t[i] : t_NOTHING,
			world_terrain(world, x+1, y-1).biome == t[i] ? t[i] : t_NOTHING,
			world_terrain(world, x-1, y  ).biome == t[i] ? t[i] : t_NOTHING,
			world_terrain(world, x+1, y  ).biome == t[i] ? t[i] : t_NOTHING,
			world_terrain(world, x-1, y+1).biome == t[i] ? t[i] : t_NOTHING,
			world_terrain(world, x,   y+1).biome == t[i] ? t[i] : t_NOTHING,
			world_terrain(world, x+1, y+1).biome == t[i] ? t[i] : t_NOTHING,
		};

		// find tile image
		char* imp_img = NULL;
		int j = -1;
		while(basic[++j].image)
			if(t[i] == basic[j].terrain)
				imp_img = basic[j].image;
		if(!imp_img)
			errx(1, "Invalid terrain type %d", t[i]);

		// add the borders
		build_tile_add_borders(world, x, y, stack, &st, b, t[i], imp_img);

		// skip the same terrain
		while(i<7 && t[i] == t[i+1])
			i++;
	}
}


static void build_tile_add_borders(World* world, int x, int y, 
		SDL_Surface* stack[MAX_STACK], int* st, Borders b, Terrain t, 
		char* imp_img)
{
	// find the most t tile around this one
	if(b.s == t && b.w == t)
		stack[(*st)++] = res2(imp_img, "_ic_sw");
	else if(b.s == t && b.e == t)
		stack[(*st)++] = res2(imp_img, "_ic_se");
	else if(b.n == t && b.w == t)
		stack[(*st)++] = res2(imp_img, "_ic_nw");
	else if(b.n == t && b.e == t)
		stack[(*st)++] = res2(imp_img, "_ic_ne");
	else if(b.n == t || b.s == t || b.w == t || b.e == t)
	{
		if(b.n == t)
			stack[(*st)++] = res2(imp_img, "_ec_s");
		if(b.s == t)
			stack[(*st)++] = res2(imp_img, "_ec_n");
		if(b.e == t)
			stack[(*st)++] = res2(imp_img, "_ec_w");
		if(b.w == t)
			stack[(*st)++] = res2(imp_img, "_ec_e");
	}
	else if(b.se == t || b.sw == t)
	{
		if(b.se == t)
			stack[(*st)++] = res2(imp_img, "_ec_nw");
		if(b.sw == t)
			stack[(*st)++] = res2(imp_img, "_ec_ne");
	}
	else if(b.ne == t || b.nw == t)
	{
		if(b.ne == t)
			stack[(*st)++] = res2(imp_img, "_ec_sw");
		if(b.nw == t)
			stack[(*st)++] = res2(imp_img, "_ec_se");
	}
}
