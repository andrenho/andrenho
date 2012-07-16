#include "sdl/ui.h"

#include <stdlib.h>
#include "SDL.h"

UI* ui_init()
{
	UI* ui = malloc(sizeof(UI));
	ui->state = EDIT;
	ui->active = 1;
	ui->lv = NULL;

	// init SDL
	if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) < 0)
	{
		fprintf(stderr, "Couldn't initialize SDL: %s\n", SDL_GetError());
	        exit(1);
	}
	if(!ui->scr)
	{
		fprintf(stderr, "Couldn't set video mode: %s\n", SDL_GetError());
		exit(1);
	}

	// init colors
	static SDL_Color colors[] = {
		{ 0, 0, 0, 0 },		// 0 - black
		{ 255, 255, 255, 0 },	// 1 - white
		{ 255, 0, 0, 0 },	// 2 - red
		{ 128, 70, 27, 0 },     // 3 - brown
		{ 0, 0, 255, 0 },       // 4 - blue
	};
	SDL_SetColors(ui->scr, colors, 0, 5);

	return ui;
}


void ui_init_level(UI* ui, Level* lv)
{
	ui->active = 1;
	ui->state = EDIT;
	ui->lv = lv;
}


void ui_draw(UI* ui)
{
}


void ui_edit(UI* ui)
{
	SDL_Event e;
	for(;;)
	{
		SDL_WaitEvent(&e);
		if(e.type == SDL_QUIT)
		{
			ui->active = 0;
			return;
		}
		else if(e.type == SDL_KEYDOWN)
		{
			switch(e.key.keysym.sym)
			{
			case SDLK_q:
				ui->active = 0;
				return;
			case SDLK_s:
				level_reset(ui->lv);
				ui->state = RUN;
				return;
			default:
				;
			}
		}
	}
}


void ui_step(UI* ui)
{
}


void ui_free(UI** ui)
{
	SDL_Quit();

	free(*ui);
	*ui = NULL;
}
