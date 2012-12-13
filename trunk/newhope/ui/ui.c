#include "ui.h"

#include <assert.h>
#include <stdlib.h>
#include <sys/time.h>
#include "SDL.h"

#include "ui/resource.h"
#include "util/log.h"
#include "util/numbers.h"
#include "util/uthash.h"
#include "world/world.h"

#define MAX_STACK 10

const int TILESIZE = 32;
const int SHOWDRAWTIME = 0;

static int ui_init_library(UI* ui);
static void ui_draw_tile(UI* ui, int x, int y, SDL_Rect* r);
static SDL_Surface* ui_tile_surface(UI* ui, int x, int y);
static void ui_image_stack(UI* ui, int x, int y, SDL_Surface* stack[MAX_STACK]);
static void ui_stack_to_char(UI* ui, SDL_Surface* stack[MAX_STACK],
		char ret[MAX_STACK * sizeof(SDL_Surface*)]);
static inline void ui_set_dirty(UI* ui, int x, int y);


typedef struct SurfaceHash {
	char id[MAX_STACK];
	SDL_Surface* sf;
	UT_hash_handle hh;
} SurfaceHash;
static SurfaceHash* sfhash = NULL;

typedef struct DirtyHash {
	uint32_t tile;
	UT_hash_handle hh;
} DirtyHash;


UI* ui_init(World* world)
{
	// initialize object
	UI* ui = malloc(sizeof(UI));
	ui->sdl_initialized = 0;
	ui->active = 1;
	ui->screen = NULL;
	ui->rx = ui->ry = 0;
	ui->world = world;
	ui->flip_next_frame = 0;
	ui->dirty = NULL;

	// initialize library
	if(!ui_init_library(ui))
	{
		ui_free(ui);
		return NULL;
	}

	// load resources
	if(!resources_load(ui))
	{
		ui_free(ui);
		return NULL;
	}

	// initial drawing
	ui_redraw(ui);

	return ui;
}


void ui_free(UI* ui)
{
	if(ui)
	{
		resources_unload(ui);
		if(ui->sdl_initialized)
		{
			struct SurfaceHash *sh, *tmp;
			HASH_ITER(hh, sfhash, sh, tmp)
			{
				HASH_DEL(sfhash, sh);
				if(sh->sf)
					SDL_FreeSurface(sh->sf);
				free(sh);
			}
			if(ui->screen)
			{
				SDL_FreeSurface(ui->screen);
				debug("SDL window terminated.");
			}
			SDL_Quit();
			debug("SDL terminated.");
		}
		struct DirtyHash *dh, *tmp;
		HASH_ITER(hh, ui->dirty, dh, tmp)
		{
			HASH_DEL(ui->dirty, dh);
			free(dh);
		}
		free(ui);
	}
}


void ui_draw(UI* ui)
{
	// will redraw:
	//   - tiles contained in `dirty` hash
	//   - full screen if ui->flip_next_frame

	struct timeval beg, end;
	if(SHOWDRAWTIME)
		gettimeofday(&beg, NULL);

	DirtyHash *d, *tmp;
	int max_rects = ui->screen->w * ui->screen->h / TILESIZE / TILESIZE * 2;
	SDL_Rect rects[max_rects];
	int numrects = 0;

	HASH_ITER(hh, ui->dirty, d, tmp)
	{
		SDL_Rect r;
		ui_draw_tile(ui, 
				d->tile % ui->world->w, 
				d->tile / ui->world->w, &r);
		if(r.w && numrects < max_rects)
		{
			rects[numrects] = r; // TODO auto-increase
			++numrects;
		}
		HASH_DEL(ui->dirty, d);
		free(d);
	}

	if(numrects > ui->screen->w * ui->screen->h / TILESIZE / TILESIZE / 3 ||
			ui->flip_next_frame)
		SDL_Flip(ui->screen);
	else
		SDL_UpdateRects(ui->screen, numrects-1, rects);
	ui->flip_next_frame = 0;

	if(SHOWDRAWTIME)
	{
		gettimeofday(&end, NULL);
		debug("%d", end.tv_usec - beg.tv_usec);
	}
}


void ui_redraw(UI* ui)
{
	int x, y;
	for(x = (ui->rx / TILESIZE); 
			x < (ui->rx + ui->screen->w) / TILESIZE + 1; 
			++x)
		for(y = (ui->ry / TILESIZE); 
				y < (ui->ry + ui->screen->h) / TILESIZE + 1; 
				++y)
			ui_set_dirty(ui, x, y);
}


void ui_moveview(UI* ui, int horiz, int vert)
{
	// move center of screen
	ui->rx += horiz;
	ui->ry += vert;

	//SDL_BlitSurface(ui->screen, NULL, ui->screen,
	//		&(SDL_Rect){ horiz, vert });
	
	// TODO - draw only the borders! this is slow!!!
	ui_redraw(ui);

	// request SDL_Flip on next frame
	ui->flip_next_frame = 1;
}


void ui_start_frame(UI* ui)
{
	ui->ticks = SDL_GetTicks() + 1000/30;
}


void ui_end_frame(UI* ui)
{
	if(SDL_GetTicks() > ui->ticks)
		debug("Frame delayed!");
	while(SDL_GetTicks() < ui->ticks)
		SDL_Delay(1);
}


/*
 * STATIC
 */


static int ui_init_library(UI* ui)
{
	if((SDL_Init(SDL_INIT_VIDEO)) != 0)
	{
		warnx("Could not initialize SDL: %s.", SDL_GetError());
		return 0;
	}
	ui->sdl_initialized = 1;
	debug("SDL initialized.");

	ui->screen = SDL_SetVideoMode(0, 0, 32, 
			SDL_SWSURFACE|SDL_RESIZABLE);
	if(!ui->screen)
	{
		warnx("Could not initialize screen: %s.", SDL_GetError());
		return 0;
	}
	debug("SDL window initialized.");
	SDL_WM_SetCaption("New Hope (version " VERSION ")", "New Hope");
	SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, 
			SDL_DEFAULT_REPEAT_INTERVAL);

	return 1;
}


static void ui_draw_tile(UI* ui, int x, int y, SDL_Rect *r)
{
	int sx = (x * TILESIZE) - ui->rx;
	int sy = (y * TILESIZE) - ui->ry;

	// important: don't free this surface - it's cached.
	SDL_Surface *sf = ui_tile_surface(ui, x, y);
	SDL_BlitSurface(sf, NULL, ui->screen, &(SDL_Rect) { sx, sy });

	if(r)
	{
		r->x = imax(sx, 0); 
		r->y = imax(sy, 0);
		if(r->x + sf->w >= ui->screen->w)
			r->w = ui->screen->w - r->x;
		else
			r->w = sf->w;
		if(r->y + sf->h >= ui->screen->h)
			r->h = ui->screen->h - r->y;
		else
			r->h = sf->h;
	}
	if(r->x > ui->screen->w || r->y > ui->screen->h)
		r = &(SDL_Rect){ 0, 0, 0, 0 };
}


static SDL_Surface* ui_tile_surface(UI* ui, int x, int y)
{
	SDL_Surface* sf = NULL;

	// build stack
	SDL_Surface* stack[MAX_STACK] = { [0 ... (MAX_STACK-1)] = NULL };
	ui_image_stack(ui, x, y, stack);

	// find hash key
	char id[RES_CHARS * sizeof(SDL_Surface*)] = { [0 ... (MAX_STACK* sizeof(SDL_Surface*)-1)] = 0 };
	ui_stack_to_char(ui, stack, id);

	// find image in hash
	SurfaceHash* sh;
	HASH_FIND_STR(sfhash, id, sh);
	if(!sh) // image not found, building it
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


static void ui_image_stack(UI* ui, int x, int y, SDL_Surface* stack[MAX_STACK])
{
	int special = 0;

	switch(world_terrain(ui->world, x, y, &special))
	{
	case t_OUT_OF_BOUNDS:
		break;
	case t_GRASS:
		switch(special)
		{
		case 0: stack[0] = res("grass_0"); break;
		case 1: stack[0] = res("grass_1"); break;
		case 2: stack[0] = res("grass_2"); break;
		case 3: stack[0] = res("grass_3"); break;
		default: abort();
		}
		break;
	default:
		errx(1, "Invalid terrain type.");
	}
}


static void ui_stack_to_char(UI* ui, SDL_Surface* stack[MAX_STACK],
		char ret[MAX_STACK * sizeof(SDL_Surface*)])
{
	memcpy(ret, stack, MAX_STACK * sizeof(SDL_Surface*));
}


static inline void ui_set_dirty(UI* ui, int x, int y)
{
	DirtyHash* d = malloc(sizeof(DirtyHash));
	d->tile = x + (y * ui->world->w);
	HASH_ADD_INT(ui->dirty, tile, d);
}
