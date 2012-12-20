#include "minimap.h"

#include <stdlib.h>
#include "SDL.h"

#include "ui/resource.h"
#include "ui/ui.h"
#include "util/numbers.h"
#include "world/world.h"


static void minimap_reset(Minimap* mm, UI* ui);
static void minimap_draw_paper(Minimap* mm, UI* ui, SDL_Rect r);


Minimap* minimap_init(World* world)
{
	Minimap* mm = malloc(sizeof(Minimap));
	mm->sf = NULL;
	mm->screen_w = mm->screen_h = 0;
	return mm;
}


void minimap_free(Minimap* mm)
{
	if(mm->sf)
		SDL_FreeSurface(mm->sf);
	free(mm);
}


void minimap_display(Minimap* mm, UI* ui)
{
	if(ui->screen->w != mm->screen_w || ui->screen->h != mm->screen_h)
		minimap_reset(mm, ui);

	SDL_Rect r = {
		(ui->screen->w/2) - (mm->sf->w/2),
		(ui->screen->h/2) - (mm->sf->h/2)
	};
	minimap_draw_paper(mm, ui, r);
	SDL_BlitSurface(mm->sf, NULL, ui->screen, &r);
	SDL_Flip(ui->screen);
	SDL_Delay(2000);
}


/*
 * STATIC
 */


static void minimap_reset(Minimap* mm, UI* ui)
{
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

	// draw map
	SDL_FillRect(mm->sf, NULL, SDL_MapRGB(mm->sf->format, 152, 180, 212));

	mm->screen_w = ui->screen->w;
	mm->screen_h = ui->screen->h;
}


static void minimap_draw_paper(Minimap* mm, UI* ui, SDL_Rect r)
{
	SDL_Rect r2 = { r.x - 20, r.y - 25, mm->sf->w + 40, mm->sf->h + 50 };

	r.x -= 60;
	r.y -= 85;
	r.w = mm->sf->w + 120;
	r.h = mm->sf->h + 170;

	// laterals
	int x, y;
	SDL_Surface *mm_n = res("mm_n"), *mm_w = res("mm_w");
	for(y=r.y+res("mm_nw")->h; y<r.y+r.h-80; y+=mm_w->h)
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
