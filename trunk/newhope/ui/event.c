#include "event.h"

#include "SDL.h"

#include "ui/ui.h"

void evt_process(UI* ui, void* world)
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
		}
	}
}
