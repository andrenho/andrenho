#include "ui.h"

#include <assert.h>
#include <stdlib.h>
#include <sys/time.h>
#include "SDL.h"

#include "ui/resource.h"
#include "ui/terrainsurface.h"
#include "util/log.h"
#include "world/world.h"

static int ui_init_library(UI* ui);


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
	ui->trsurf = trsurf_init(world);

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
	trsurf_resize(ui->trsurf, ui->screen->w, ui->screen->h);

	return ui;
}


void ui_free(UI* ui)
{
	if(ui)
	{
		resources_unload(ui);
		if(ui->sdl_initialized)
		{
			if(ui->screen)
			{
				SDL_FreeSurface(ui->screen);
				debug("SDL window terminated.");
			}
			SDL_Quit();
			debug("SDL terminated.");
		}
		trsurf_free(ui->trsurf);
		free(ui);
	}
}


void ui_draw(UI* ui)
{
	SDL_Rect* r;
	int numrects;
	int flip = trsurf_areas_to_redraw(ui->trsurf, &r, &numrects);

	if(flip)
	{
		SDL_Rect r = { ui->rx % TILESIZE, ui->ry % TILESIZE };
		SDL_BlitSurface(ui->trsurf->sf, NULL, ui->screen, &r);
		SDL_Flip(ui->screen);
	}
	else
	{
		// TODO
		abort();
	}
}


void ui_moveview(UI* ui, int horiz, int vert)
{
	// move center of screen
	ui->rx += horiz;
	ui->ry += vert;

	trsurf_set_topleft(ui->trsurf, -(ui->rx/TILESIZE), -(ui->ry/TILESIZE));
}


void ui_start_frame(UI* ui)
{
	ui->ticks = SDL_GetTicks() + 1000/60;
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
