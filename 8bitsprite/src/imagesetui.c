#include "imagesetui.h"

#include "SDL.h"

#include "util.h"
#include "editor.h"

static int image_selected = -1;
static Imageset* imageset;
static int n_buttons;
static SDL_Rect* buttons;


static void change_image(int* n_buttons, SDL_Rect** buttons);
static int new_image();
static void next_image(int n);


void imageset_ui_run(Imageset* is)
{
	(void) image_selected;
	int i;

	imageset = is;

	change_image(&n_buttons, &buttons);

	for(;;)
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
							image_selected = new_image();
							change_image(&n_buttons, &buttons);
							break;
						case 1:
							next_image(-1);
							break;
						case 2:
							next_image(1);
							break;
						}
				}
				break;
			case SDL_KEYDOWN:
				switch(e.key.keysym.sym)
				{
				case SDLK_n:
					image_selected = new_image();
					change_image(&n_buttons, &buttons);
					break;
				default:
					break;
				}
			}
		}
	}
}


static void change_image(int* n_buttons, SDL_Rect** buttons)
{
	// draw buttons
	SDL_FillRect(screen, NULL, 0);

	if(image_selected == -1)
	{
		*n_buttons = 1;
		*buttons = draw_buttons("New Image [N]", 0);
	}
	else
	{
		*n_buttons = 5;
		*buttons = draw_buttons("New Image [N]",
				        "Previous [<]",
					"Next [>]",
					"Edit [Enter]",
					"Delete [Del]", 0);

		Image* img = utarray_eltptr(imageset->images, image_selected);
		SDL_Rect r = { screen->w/2 - img->sf->w/2,
			       screen->h/2 - img->sf->h/2 };
		SDL_BlitSurface(img->sf, NULL, screen, &r);
	}
	
	SDL_Flip(screen);
}


static int new_image()
{
	Image* img = imageset_add_image(imageset);
	editor_run(img);
	printf("%d\n", utarray_len(imageset->images) - 1);
	return utarray_len(imageset->images) - 1;
}


static void next_image(int n)
{
	if(n == -1)
	{
		if(image_selected != 0)
		{
			--image_selected;
			change_image(&n_buttons, &buttons);
		}
	}
	else if(n == 1)
	{
		if(image_selected != utarray_len(imageset->images)-1)
		{
			++image_selected;
			change_image(&n_buttons, &buttons);
		}
	}
	else
		abort();
}
