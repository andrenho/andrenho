#include "ui.h"

#include <stdlib.h>
#include <syslog.h>
#include "SDL.h"


int ui_init_library(UI* ui);
int ui_load_resources(UI* ui);


UI* ui_init()
{
	// initialize object
	UI* ui = malloc(sizeof(UI));
	ui->sdl_initialized = 0;

	// initialize library
	if(ui_init_library(ui) != 0)
	{
		ui_free(ui);
		return NULL;
	}
	syslog(LOG_ERR, "SDL initialized.");

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


/*
 * PRIVATE
 */


int ui_init_library(UI* ui)
{
	if((SDL_Init(SDL_INIT_VIDEO)) != 0)
	{
		syslog(LOG_ERR, "Could not initialize SDL: %s.\n", SDL_GetError());
		return 0;
	}

	ui->sdl_initialized = 1;
	return -1;
}


int ui_load_resources(UI* ui)
{
	return -1;
}
