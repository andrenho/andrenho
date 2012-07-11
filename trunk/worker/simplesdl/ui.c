#include "simplesdl/ui.h"

#include <stdlib.h>
#include <stdio.h>

#define TILE 12


static void square(UI* ui, int x, int y, int w, int h, int fg, int bg);


UI* ui_init()
{
	UI* ui = malloc(sizeof(UI));
	ui->active = 1;
	ui->state = EDIT;
	ui->lv = NULL;
	ui->scr = SDL_SetVideoMode(400, 300, 8, SDL_SWSURFACE);

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
	SDL_FillRect(ui->scr, NULL, 1);

	// structures
	Structure* st = ui->lv->structures;
	do
	{
		switch(st->structure)
		{
		case WALL:
			square(ui, st->x * TILE, st->y * TILE, TILE+1, TILE+1, 
					0, 1);
			break;
		case ENTRANCE:
			square(ui, st->x * TILE, st->y * TILE, TILE+1, TILE+1, 
					2, 1);
			break;
		case BOXSTART:
			if(ui->state == EDIT)
				square(ui, st->x * TILE - 1, st->y * TILE - 1, 
						TILE, TILE, 3, 3);
			break;
		case DOOR:
			square(ui, st->x * TILE, st->y * TILE, TILE+1, TILE+1, 
					4, 1);
			break;
		default:
			;
		}
	} while((st = st->next));

	// objects
	if(ui->state == RUN)
	{
		Object* o = ui->lv->objects;
		do
		{
			switch(o->object)
			{
			case WORKER:
				square(ui, o->x * TILE + 2, o->y * TILE + 2, 
						TILE-3, TILE-3, 2, 2);
				break;
			case BOX:
				square(ui, o->x * TILE - 1, o->y * TILE - 1, 
						TILE, TILE, 3, 3);
				break;
			}
		} while((o = o->next));
	}

	SDL_Flip(ui->scr);
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


static void square(UI* ui, int x, int y, int w, int h, int fg, int bg)
{
	SDL_Rect r1 = { x, y, w, h };
	SDL_Rect r2 = { x+1, y+1, w-2, h-2 };
	SDL_FillRect(ui->scr, &r1, fg);
	SDL_FillRect(ui->scr, &r2, bg);
}
