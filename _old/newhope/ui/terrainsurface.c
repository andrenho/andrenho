#include "terrainsurface.h"

#include <assert.h>
#include "SDL.h"

#include "ui/buildtile.h"
#include "ui/resource.h"
#include "util/log.h"
#include "util/uthash.h"


typedef struct SurfaceHash {
	char id[MAX_STACK];
	SDL_Surface* sf;
	UT_hash_handle hh;
} SurfaceHash;
static SurfaceHash* sfhash = NULL; // TODO - add to structure



static void trsurf_redraw(TerrainSurface* ts);
static SDL_Surface* trsurf_tile_sf(TerrainSurface* ts, int x, int y);
static void stack_to_char(SDL_Surface* stack[MAX_STACK],
		char ret[MAX_STACK * 12]);
static void trsurf_draw_tile(TerrainSurface* ts, int x, int y);



TerrainSurface* trsurf_init(struct World* world)
{
	TerrainSurface* ts = malloc(sizeof(TerrainSurface));
	ts->sf = NULL;
	ts->world = world;
	ts->x = ts->y = ts->w = ts->h = 0;
	return ts;
}


void trsurf_free(TerrainSurface* ts)
{
	struct SurfaceHash *sh, *tmp;
	HASH_ITER(hh, sfhash, sh, tmp)
	{
		HASH_DEL(sfhash, sh);
		if(sh->sf)
			SDL_FreeSurface(sh->sf);
		free(sh);
	}	
	if(ts->sf)
		SDL_FreeSurface(ts->sf);
	free(ts);
}


void trsurf_resize(TerrainSurface* ts, int w, int h)
{
	if(ts->sf)
		SDL_FreeSurface(ts->sf);
	SDL_Surface* sf = SDL_CreateRGBSurface(SDL_SWSURFACE, 
			w + (TILESIZE + (w % TILESIZE)), 
			h + (TILESIZE + (h % TILESIZE)), 32,
			0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000);
	ts->sf = SDL_DisplayFormat(sf);
	SDL_FreeSurface(sf);
	if(!ts->sf)
		errx(1, "Error creating surface: %s", SDL_GetError());
	ts->w = ts->sf->w / TILESIZE;
	ts->h = ts->sf->h / TILESIZE;
	trsurf_redraw(ts);

	debug("window resize resquested: %d %d", w, h);
	debug("trsurf resize: %d %d (%d %d)", ts->sf->w, ts->sf->h, ts->w, ts->h);
}


int trsurf_areas_to_redraw(TerrainSurface* ts, struct SDL_Rect** r, int* nrect)
{
	return 1;
}


void trsurf_set_topleft(TerrainSurface* ts, int x, int y)
{
	int nx, ny;

	if(ts->x == x && ts->y == y)
		return;

	// debug("changed topleft to %d %d", x, y);

	SDL_Rect r = { (ts->x - x)*TILESIZE, (ts->y - y)*TILESIZE };
	SDL_BlitSurface(ts->sf, NULL, ts->sf, &r);

	int tsx = ts->x, 
	    tsy = ts->y;

	ts->x = x;
	ts->y = y;

	if(x > tsx)
	{
		for(nx=(ts->w + ts->x - (x - tsx)); nx < (ts->w + ts->x); nx++)
			for(ny=ts->y; ny < (ts->h + ts->y); ny++)
				trsurf_draw_tile(ts, nx, ny);
	}
	else if(x < tsx)
	{
		for(nx=ts->x; nx < (ts->x + tsx - x); nx++)
			for(ny=ts->y; ny < (ts->h + ts->y); ny++)
				trsurf_draw_tile(ts, nx, ny);
	}

	if(y > tsy)
	{
		for(ny=(ts->h + ts->y - (y - tsy)); ny < (ts->h + ts->y); ny++)
			for(nx=ts->x; nx < (ts->w + ts->x); nx++)
				trsurf_draw_tile(ts, nx, ny);
	}
	else if(y < tsy)
	{
		for(ny=ts->y; ny < (ts->y + tsy - y); ny++)
			for(nx=ts->x; nx < (ts->w + ts->x); nx++)
				trsurf_draw_tile(ts, nx, ny);
	}
}


/*
 * STATIC
 */
static void trsurf_redraw(TerrainSurface* ts)
{
	int x, y;

	// SDL_FillRect(ts->sf, NULL, 0);
	for(x=ts->x; x<(ts->x + ts->w); x++)
		for(y=ts->y; y<(ts->y + ts->h); y++)
			trsurf_draw_tile(ts, x, y);
}


static void trsurf_draw_tile(TerrainSurface* ts, int x, int y)
{
	//debug("drawing tile %d %d", x, y);

	SDL_Rect r = { 
		(x - ts->x) * TILESIZE, 
		(y - ts->y) * TILESIZE, 
		TILESIZE, TILESIZE 
	};
	SDL_FillRect(ts->sf, &r, 0); // TODO - ???
	SDL_BlitSurface(trsurf_tile_sf(ts, x, y), NULL, ts->sf, &r);

}


static SDL_Surface* trsurf_tile_sf(TerrainSurface* ts, int x, int y)
{
	SDL_Surface *sf;
	
	// build stack
	SDL_Surface* stack[MAX_STACK] = { [0 ... (MAX_STACK-1)] = NULL };
	build_tile(ts->world, x, y, stack);

	// find hash key
	char id[RES_CHARS * 12] = { [0 ... (MAX_STACK* 12-1)] = 0 };
	stack_to_char(stack, id);

	// find image in hash
	SurfaceHash* sh;
	HASH_FIND_STR(sfhash, id, sh);
	if(!sh) // image not found, build it
	{
		// create image
		int i = 0;
		SDL_Surface* _sf = SDL_CreateRGBSurface(SDL_SWSURFACE,
				TILESIZE, TILESIZE, 32, 
				0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000);
		sf = SDL_DisplayFormat(_sf);
		SDL_FreeSurface(_sf);
		SDL_FillRect(sf, NULL, 0);
		while(stack[i])
		{
			SDL_BlitSurface(stack[i], NULL, sf, NULL);
			i++;
		}

		// add to hash
		sh = malloc(sizeof(SurfaceHash));
		strcpy(sh->id, id);
		sh->sf = sf;
		HASH_ADD_STR(sfhash, id, sh);
	}
	else
		sf = sh->sf;

	assert(sf);
	return sf;
}


static void stack_to_char(SDL_Surface* stack[MAX_STACK],
		char ret[MAX_STACK * 12])
{
	//memcpy(ret, stack, MAX_STACK * 12);
	int i = -1;
	int p = 0;
	while(stack[++i])
		p += sprintf(&ret[p], "%p", (void*)stack[i]);
}
