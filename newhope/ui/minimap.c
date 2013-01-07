#include "minimap.h"

#include <assert.h>
#include <stdlib.h>
#include "SDL.h"
#include "SDL_thread.h"

#include "ui/resource.h"
#include "ui/terminal.h"
#include "ui/ui.h"
#include "util/countset.h"
#include "util/log.h"
#include "util/numbers.h"
#include "util/sdlu.h"
#include "world/mapbuild.h"
#include "world/world.h"

struct {
	Terrain terrain;
	int r, g, b;
	Uint32 c;
} clrs[] = {
	{ t_WATER, 152, 180, 212, 0 },
	{ t_DIRT, 0xbe, 0xa3, 0x76, 0 },
	{ t_GRASS, 59, 122, 87, 0 },
	{ t_INVALID, 0, 0, 0, 0 },
};


static int minimap_create(void* ui);
static void minimap_draw_paper(Minimap* mm, UI* ui, SDL_Rect r);
static void minimap_events(Minimap* mm);
static void minimap_mouse_motion(Minimap* mm, SDL_MouseMotionEvent me);
static int minimap_mouse_click(Minimap* mm, SDL_MouseButtonEvent me);


Minimap* minimap_init(World* world, UI* ui)
{
	Minimap* mm = malloc(sizeof(Minimap));
	mm->sf = NULL;
	mm->ui = ui;
	mm->screen_w = mm->screen_h = 0;
	mm->thread = NULL;
	mm->killthread = 0;
	mm->sz = 0;
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
	mm->sz = imin(ui->screen->w, ui->screen->h) - 250;
	SDL_Rect r = {
		(ui->screen->w/2) - mm->sz/2,
		(ui->screen->h/2) - mm->sz/2,
		mm->sz, mm->sz
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
	
	minimap_events(mm);
}


void minimap_reset(Minimap* mm, UI* ui)
{
	minimap_kill_thread(mm);
	mm->thread = SDL_CreateThread(&minimap_create, (void*)ui);
}


void minimap_kill_thread(Minimap* mm)
{
	if(mm->thread)
	{
		int n;
		mm->killthread = 1;
		SDL_WaitThread(mm->thread, &n);
		debug("Minimap thread killed.");
	}
	mm->killthread = 0;
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
	mm->sz = imin(ui->screen->w, ui->screen->h) - 250;
	SDL_Surface* sf = SDL_CreateRGBSurface(SDL_SWSURFACE, 
			mm->sz, mm->sz, 32,
			0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000);
	mm->sf = SDL_DisplayFormat(sf);
	SDL_FreeSurface(sf);
	mm->screen_w = ui->screen->w;
	mm->screen_h = ui->screen->h;

	// setup colors
	int i=-1;
	while(clrs[++i].terrain != t_INVALID)
		clrs[i].c = SDL_MapRGB(mm->sf->format, clrs[i].r,
				clrs[i].g, clrs[i].b);

	// draw map
	int px, py;
	double x, y, ps = (double)ui->world->w / (double)mm->sz;
	for(x=px=0; x<ui->world->w && px < mm->sz; x+=ps, px++)
	{
		for(y=py=0; y<ui->world->h && py < mm->sz; y+=ps, py++)
		{
			if(mm->killthread)
				return 0;
			Terrain t = world_terrain(ui->world, x, y).biome;
			i = -1;
			while(clrs[++i].terrain != t_INVALID)
				if(t == clrs[i].terrain)
				{
					Uint8 *p = (Uint8*)mm->sf->pixels 
						+ (py * mm->sf->pitch)
						+ (px * 4);
					*(Uint32*)p = clrs[i].c;
				}
		}
	}

	// draw rivers
	ps = (double)ui->world->w / (double)mm->sz;
	for(i=0; i<ui->world->map->n_rivers; i++)
	{
		PointList* river = &ui->world->map->rivers[i];
		for(int j=0; j<river->n-1; j++)
		{
			Point p1 = river->points[j];
			Point p2 = river->points[j+1];
			Uint32 c = SDL_MapRGB(mm->sf->format, 152, 180, 212);
			double x0 = iminmax((double)p1.x / ps, 0, mm->sf->w-3);
			double x1 = iminmax((double)p1.y / ps, 0, mm->sf->w-3);;
			double y0 = iminmax((double)p2.x / ps, 0, mm->sf->h-3);;
			double y1 = iminmax((double)p2.y / ps, 0, mm->sf->h-3);;
			printf("%f %f %f %f\n", x0, x1, y0, y1);
			draw_line(mm->sf, x0, x1, y0, y1, 3, c);
		}
	}

	debug("Minimap redrawn.");

	mm->thread = NULL;
	return 0;
}


static void minimap_draw_paper(Minimap* mm, UI* ui, SDL_Rect r)
{
	SDL_Rect r2 = { r.x - 20, r.y - 20, r.w + 40, r.h + 40 };

	r.x -= 60;
	r.y -= 85;
	r.w = r.w + 120;
	r.h = r.h + 170;

	// shadow - TODO
	/*
	SDL_Surface *shadow2 = SDL_CreateRGBSurface(SDL_SWSURFACE, r.w, r.h, 32,
			0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000);
	SDL_Surface* shadow = SDL_DisplayFormat(shadow2);
	SDL_FreeSurface(shadow2);
	SDL_SetAlpha(shadow, SDL_SRCALPHA|SDL_RLEACCEL, 128);
	SDL_BlitSurface(shadow, NULL, ui->screen, &(SDL_Rect){ r.x+10, r.y+30 });
	SDL_FreeSurface(shadow);
	*/

	// laterals
	int x, y;
	SDL_Surface *mm_n = res("mm_n"), *mm_w = res("mm_w");
	for(y=r.y+res("mm_nw")->h; y<r.y+r.h-60; y+=mm_w->h)
	{
		SDL_BlitSurface(mm_w, NULL, ui->screen, &(SDL_Rect){ r.x, y });
		SDL_BlitSurface(res("mm_e"), NULL, ui->screen, &(SDL_Rect){ 
				r.x + r.w - res("mm_e")->w, y });
	}
	for(x=r.x+res("mm_nw")->w; x<r.x+r.w-res("mm_ne")->w; x+=mm_n->w)
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


static void minimap_events(Minimap* mm)
{
	SDL_Event e;
	int active = 1;
	
	while(active)
	{
		while(SDL_PollEvent(&e))
		{
			switch(e.type)
			{
			case SDL_MOUSEMOTION:
				minimap_mouse_motion(mm, e.motion);
				break;
			case SDL_MOUSEBUTTONDOWN:
				if(e.button.button == SDL_BUTTON_LEFT)
					active = minimap_mouse_click(mm, e.button);
				break;
			}
		}
		SDL_Delay(1000/30);
	}
}


static void minimap_mouse_motion(Minimap* mm, SDL_MouseMotionEvent me)
{
	SDL_Rect r = {
		(mm->ui->screen->w/2) - mm->sz/2,
		(mm->ui->screen->h/2) - mm->sz/2,
		mm->sz, mm->sz
	};
	if(inside(me.x, me.y, r))
		terminal_state(mm->ui->terminal, PARTIAL);
	else
		terminal_state(mm->ui->terminal, CLOSED);
}


static int minimap_mouse_click(Minimap* mm, SDL_MouseButtonEvent me)
{
	SDL_Rect r = {
		(mm->ui->screen->w/2) - mm->sz/2,
		(mm->ui->screen->h/2) - mm->sz/2,
		mm->sz, mm->sz
	};
	if(!inside(me.x, me.y, r))
		return 0;
	else
		return 1;
}
