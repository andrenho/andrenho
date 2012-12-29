#include "minimap.h"

#include <assert.h>
#include <stdlib.h>
#include "SDL.h"
#include "SDL_thread.h"

#include "ui/resource.h"
#include "ui/ui.h"
#include "util/countset.h"
#include "util/log.h"
#include "util/numbers.h"
#include "world/world.h"

struct {
	Terrain terrain;
	int r, g, b;
	Uint32 c;
} clrs[] = {
	{ t_WATER, 152, 180, 212, 0 },
	{ t_DIRT, 0xbe, 0xa3, 0x76, 0 },
	{ t_INVALID, 0, 0, 0, 0 },
};


static int minimap_create(void* ui);
static void minimap_draw_paper(Minimap* mm, UI* ui, SDL_Rect r);


Minimap* minimap_init(World* world)
{
	Minimap* mm = malloc(sizeof(Minimap));
	mm->sf = NULL;
	mm->screen_w = mm->screen_h = 0;
	mm->thread = NULL;
	return mm;
}


void minimap_free(Minimap* mm)
{
	minimap_kill_thread(mm);
	if(mm->sf)
		SDL_FreeSurface(mm->sf);
	free(mm);
}


void minimap_display(Minimap* mm, UI* ui)
{
	int sz = imin(ui->screen->w, ui->screen->h) - 250;
	SDL_Rect r = {
		(ui->screen->w/2) - sz/2,
		(ui->screen->h/2) - sz/2,
		sz, sz
	};
	minimap_draw_paper(mm, ui, r);
	SDL_Flip(ui->screen);

	/*
	if(ui->screen->w != mm->screen_w || ui->screen->h != mm->screen_h)
		minimap_reset(mm, ui);
	*/
	// wait for thread to finish
	if(mm->thread)
	{
		int n;
		SDL_WaitThread(mm->thread, &n);
	}

	SDL_BlitSurface(mm->sf, NULL, ui->screen, &r);
	SDL_Flip(ui->screen);
	SDL_Delay(2000);
}


void minimap_reset(Minimap* mm, UI* ui)
{
	minimap_kill_thread(mm);
	mm->thread = SDL_CreateThread(&minimap_create, (void*)ui);
}


void minimap_kill_thread(Minimap* mm)
{
	if(mm->thread)
		SDL_KillThread(mm->thread);
}


/*
 * STATIC
 */

static int minimap_create(void* vui)
{
	debug("Redrawing minimap.");

	UI* ui = (UI*)vui;
	Minimap* mm = ui->mm;

	assert(ui->screen);

	// free surface
	if(mm->sf)
		SDL_FreeSurface(mm->sf);

	// create surface
	int sz = imin(ui->screen->w, ui->screen->h) - 250;
	SDL_Surface* sf = SDL_CreateRGBSurface(SDL_SWSURFACE, 
			sz, sz, 32,
			0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000);
	mm->sf = SDL_DisplayFormat(sf);
	SDL_FreeSurface(sf);
	mm->screen_w = ui->screen->w;
	mm->screen_h = ui->screen->h;

	// setup clrs
	int i=-1;
	while(clrs[++i].terrain != t_INVALID)
		clrs[i].c = SDL_MapRGB(mm->sf->format, clrs[i].r,
				clrs[i].g, clrs[i].b);

	// draw map
	int x, y, x2, y2, px, py;
	int ps = ui->world->w / sz;
	for(x=px=0; x<ui->world->w && px < sz; x+=ps, px++)
		for(y=py=0; y<ui->world->h && py < sz; y+=ps, py++)
		{
			CountSet* cs = countset();
			for(x2=x; x2<x+ps; x2++)
				for(y2=y; y2<y+ps; y2++)
				{
					TerrainSet ts = world_terrain(
							ui->world, x, y);
					cs_add(cs, (ts.topsoil != t_NOTHING) ? 
							ts.topsoil : ts.biome);
				}
			Terrain t = cs_highest(cs);
			i = -1;
			while(clrs[++i].terrain != t_INVALID)
				if(t == clrs[i].terrain)
				{
					Uint8 *p = (Uint8*)mm->sf->pixels 
						+ (py * mm->sf->pitch)
						+ (px * 4);
					*(Uint32*)p = clrs[i].c;
				}
			cs_free(cs);
		}

	debug("Minimap redrawn.");

	mm->thread = NULL;
	return 0;
}


static void minimap_draw_paper(Minimap* mm, UI* ui, SDL_Rect r)
{
	SDL_Rect r2 = { r.x - 20, r.y - 25, r.w + 40, r.h + 50 };

	r.x -= 60;
	r.y -= 85;
	r.w = r.w + 120;
	r.h = r.h + 170;

	// laterals
	int x, y;
	SDL_Surface *mm_n = res("mm_n"), *mm_w = res("mm_w");
	for(y=r.y+res("mm_nw")->h; y<r.y+r.h-60; y+=mm_w->h)
	{
		SDL_BlitSurface(mm_w, NULL, ui->screen, &(SDL_Rect){ r.x, y });
		SDL_BlitSurface(res("mm_e"), NULL, ui->screen, &(SDL_Rect){ 
				r.x + r.w - res("mm_e")->w, y });
	}
	for(x=r.x+res("mm_nw")->w; x<r.x+r.w-50; x+=mm_n->w)
	{
		SDL_BlitSurface(mm_n, NULL, ui->screen, &(SDL_Rect){ x, r.y });
		SDL_BlitSurface(res("mm_s"), NULL, ui->screen, &(SDL_Rect){ 
				x, r.y + r.h - res("mm_s")->h });
	}

	// borders
	int tr = r.x;
	int dfw = r.w - res("mm_ne")->w,
	    dfh = r.h - res("mm_se")->h;
	SDL_BlitSurface(res("mm_nw"), NULL, ui->screen, &r);
	r.x += dfw;
	SDL_BlitSurface(res("mm_ne"), NULL, ui->screen, &r);
	r.y += dfh;
	SDL_BlitSurface(res("mm_se"), NULL, ui->screen, &r);
	r.x = tr;
	SDL_BlitSurface(res("mm_sw"), NULL, ui->screen, &r);

	// middle
	SDL_FillRect(ui->screen, &r2, 
			SDL_MapRGB(ui->screen->format, 210, 183, 119));
}
