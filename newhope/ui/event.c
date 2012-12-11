#include "event.h"

#include "SDL.h"

#include "ui/ui.h"
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
		case SDL_QUIT:
			ui->active = 0;
			break;
		case SDL_KEYDOWN:
			evt_keypress(ui, world, e.key);
			break;
		}
	}
}


static void evt_keypress(UI* ui, World* world, SDL_KeyboardEvent k)
{
	switch(k.keysym.sym)
	{
	case SDLK_h:
		ui_moveview(ui, -1, 0);
		break;
	case SDLK_j:
		ui_moveview(ui, 0, 1);
		break;
	case SDLK_k:
		ui_moveview(ui, 0, -1);
		break;
	case SDLK_l:
		ui_moveview(ui, 1, 0);
		break;
	default:
		break;
	}
}
