#include "ui.h"

#include <stdlib.h>
#include "SDL.h"
#include "SDL_image.h"

#include "ui/resource.h"
#include "util/log.h"

static int ui_init_library(UI* ui);


UI* ui_init()
{
	// initialize object
	UI* ui = malloc(sizeof(UI));
	ui->sdl_initialized = 0;
	ui->active = 1;
	ui->screen = NULL;

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
			IMG_Quit();
			SDL_Quit();
			debug("SDL terminated.");
		}
		free(ui);
	}
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

	if(IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG)
	{
		warnx("Could not initialize SDL_image: %s.", IMG_GetError());
		return 0;
	}
	debug("SDL_image initialized.");

	ui->screen = SDL_SetVideoMode(800, 600, 32, 
			SDL_SWSURFACE|SDL_RESIZABLE);
	if(!ui->screen)
	{
		warnx("Could not initialize screen: %s.", SDL_GetError());
		return 0;
	}
	debug("SDL window initialized.");
	SDL_WM_SetCaption("New Hope (version " VERSION ")", "New Hope");

	return 1;
}
