#include "ui.h"

#include <stdlib.h>
#include "SDL.h"

#include "util/log.h"


static int ui_init_library(UI* ui);
static int ui_load_resources(UI* ui);


UI* ui_init()
{
	// initialize object
	UI* ui = malloc(sizeof(UI));
	ui->sdl_initialized = 0;
	ui->active = 1;
	ui->screen = NULL;

	// initialize library
	if(ui_init_library(ui) != 0)
	{
		ui_free(ui);
		return NULL;
	}
	debug("SDL initialized.");

	// load resources
	if(ui_load_resources(ui) != 0)
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
		if(ui->sdl_initialized)
			SDL_Quit();
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
		warnx("Could not initialize SDL: %s.\n", SDL_GetError());
		return -1;
	}
	ui->sdl_initialized = 1;

	ui->screen = SDL_SetVideoMode(800, 600, 32, 
			SDL_SWSURFACE|SDL_RESIZABLE);
	if(!ui->screen)
	{
		warnx("Could not initialize screen: %s\n", SDL_GetError());
		return -1;
	}
	SDL_WM_SetCaption("New Hope (version " VERSION ")", "New Hope");

	return 0;
}


static int ui_load_resources(UI* ui)
{
	return 0;
}
