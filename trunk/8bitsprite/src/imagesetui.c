#include "imagesetui.h"

#include "SDL.h"

#include "util.h"

static int image_selected = -1;
static Imageset* imageset;


static void new_image();


void imageset_ui_run(Imageset* is)
{
	(void) image_selected;
	int i;

	imageset = is;

	// draw buttons
	SDL_FillRect(screen, NULL, 0);
	int n_buttons = 1;
	SDL_Rect* buttons = draw_buttons("New Image (C-N)", 0);
	SDL_Flip(screen);

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
			case SDL_MOUSEBUTTONDOWN:
				for(i=0; i<n_buttons; i++)
				{
					SDL_Rect r = buttons[i];
					if(e.button.x >= r.x && e.button.y >= r.y && e.button.x < r.x+r.w && e.button.y < r.y+r.h)
						switch(i)
						{
						case 0: // new image
							new_image();
							break;
						}
				}
				break;
			}
		}
	}
}


static void new_image()
{
	Image* img = imageset_add_image(imageset);
	(void) img;
}
