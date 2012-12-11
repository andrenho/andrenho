#include "ui.h"

#include <stdlib.h>
#include "SDL.h"

#include "ui/resource.h"
#include "util/log.h"

const int TILESIZE = 32;

static int ui_init_library(UI* ui);


UI* ui_init()
{
	// initialize object
	UI* ui = malloc(sizeof(UI));
	ui->sdl_initialized = 0;
	ui->active = 1;
	ui->screen = NULL;
	ui->rx = ui->ry = 0;

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
		free(ui);
	}
}


void ui_draw(UI* ui)
{
	SDL_FillRect(ui->screen, NULL, 0);

	int x = ui->rx / TILESIZE,
	    y = ui->ry / TILESIZE;
	int sx = ui->rx % TILESIZE,
	    sy = ui->ry % TILESIZE;
	SDL_BlitSurface(res("grassm"), NULL, ui->screen,
			&(SDL_Rect) { sx, sy });
	SDL_Flip(ui->screen);
}


void ui_moveview(UI* ui, int horiz, int vert)
{
	ui->rx += horiz;
	ui->ry += vert;
}


void ui_start_frame(UI* ui)
{
	ui->ticks = SDL_GetTicks() + 1000/60;
}


void ui_end_frame(UI* ui)
{
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

	ui->screen = SDL_SetVideoMode(800, 600, 32, 
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
