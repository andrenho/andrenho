#include "event.h"

#include "SDL.h"

#include "ui/ui.h"
#include "ui/terrainsurface.h"
#include "world/world.h"


static void evt_keypress(UI* ui, World* world, SDL_KeyboardEvent k);


void evt_process(UI* ui, World* world)
{
	(void) world;

	SDL_Event e;
	while(SDL_PollEvent(&e))
	{
		switch(e.type)
		{
		case SDL_VIDEORESIZE:
			//SDL_FreeSurface(ui->screen);
			ui->screen = SDL_SetVideoMode(e.resize.w, e.resize.h, 32, 
				SDL_SWSURFACE|SDL_RESIZABLE);
			trsurf_resize(ui->trsurf, ui->screen->w, ui->screen->h);
			break;
		case SDL_KEYDOWN:
			evt_keypress(ui, world, e.key);
			break;
		case SDL_QUIT:
			ui->active = 0;
			break;
		}
	}
}


static void evt_keypress(UI* ui, World* world, SDL_KeyboardEvent k)
{
	int s = 5;
	
	Uint8 *ks = SDL_GetKeyState(NULL);
	if(ks[SDLK_LSHIFT])
		s = 40;

	switch(k.keysym.sym)
	{
	case SDLK_LEFT:
		ui_moveview(ui, -s, 0);
		break;
	case SDLK_DOWN:
		ui_moveview(ui, 0, s);
		break;
	case SDLK_UP:
		ui_moveview(ui, 0, -s);
		break;
	case SDLK_RIGHT:
		ui_moveview(ui, s, 0);
		break;
	default:
		break;
	}
}
