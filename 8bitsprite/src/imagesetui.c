#include "imagesetui.h"

#include "SDL.h"

#include "util.h"

static int image_selected = -1;

void imageset_ui_run(Imageset* is)
{
	(void) image_selected;

	// draw buttons
	SDL_FillRect(screen, NULL, 0);
	SDL_Rect* buttons = draw_buttons("New Image (C-N)", "Something");
	SDL_Flip(screen);

	(void) buttons;

	int running = 1;
	while(running)
	{
		SDL_Event e;
		while(SDL_PollEvent(&e))
		{
			switch(e.type)
			{
			case SDL_QUIT:
				// TODO - save?
				SDL_Quit();
				exit(0);
			}
		}
	}
}
