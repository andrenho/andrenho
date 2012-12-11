#include "ui.h"

#include <stdlib.h>
#include "SDL.h"

#include "ui/resource.h"
#include "util/log.h"
#include "world/world.h"

const int TILESIZE = 32;
const int MAX_STACK = 10;

static int ui_init_library(UI* ui);
static SDL_Surface* ui_tile_surface(UI* ui, int x, int y);
static void ui_image_stack(UI* ui, int x, int y, Resource stack[MAX_STACK]);

UI* ui_init(World* world)
{
	// initialize object
	UI* ui = malloc(sizeof(UI));
	ui->sdl_initialized = 0;
	ui->active = 1;
	ui->screen = NULL;
	ui->rx = ui->ry = 0;
	ui->world = world;

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
	SDL_Flip(ui->screen);
}


void ui_redraw(UI* ui)
{
	SDL_FillRect(ui->screen, NULL, 0);

	int x, y, sx, sy;
	for(
			x = -ui->rx / TILESIZE - 1, 
			sx = ui->rx % TILESIZE - TILESIZE;
			sx < ui->screen->w; 
			sx += TILESIZE, ++x)
		for(
				y = -ui->ry / TILESIZE - 1, 
				sy = ui->ry % TILESIZE - TILESIZE;
				sy < ui->screen->w;
				sy += TILESIZE, ++y)
		{
			// important: don't free this surface - it's cached.
			SDL_Surface *sf = ui_tile_surface(ui, x, y);
			SDL_BlitSurface(sf, NULL, 
					ui->screen, &(SDL_Rect) { sx, sy });
		}
}


void ui_moveview(UI* ui, int horiz, int vert)
{
	ui->rx += horiz;
	ui->ry += vert;
	SDL_BlitSurface(ui->screen, NULL, ui->screen, 
			&(SDL_Rect){ horiz, vert });
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


static SDL_Surface* ui_tile_surface(UI* ui, int x, int y)
{
	Resource stack[MAX_STACK];
	ui_image_stack(ui, x, y, stack);
	
	// TODO - make a stack of the drawings
	int i = 0;
	SDL_Surface* _sf = SDL_CreateRGBSurface(SDL_SWSURFACE,
			TILESIZE, TILESIZE, 32, 
			0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000);
	SDL_Surface* sf = SDL_DisplayFormat(_sf);
	SDL_FreeSurface(_sf);
	while(stack[i] != NOTHING)
	{
		SDL_BlitSurface(res(stack[i]), NULL, sf, NULL);
		i++;
	}

	return sf;
}


static void ui_image_stack(UI* ui, int x, int y, Resource stack[MAX_STACK])
{
	switch(world_terrain(ui->world, x, y))
	{
	case t_OUT_OF_BOUNDS:
		stack[0] = NOTHING;
		break;
	case t_GRASS:
		stack[0] = GRASSM;
		stack[1] = NOTHING;
		break;
	default:
		errx(1, "Invalid terrain type.");
	}
}
