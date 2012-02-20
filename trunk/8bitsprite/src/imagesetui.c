#include "imagesetui.h"

#include "SDL.h"

#include "util.h"
#include "editor.h"

static int image_selected = -1;
static Imageset* imageset;
static int n_buttons;
static SDL_Rect* buttons;


static void click(int x, int y);
static void keypress(SDLKey sym);

static void change_image(int* n_buttons, SDL_Rect** buttons);
static int new_image();
static void edit_image();
static void delete_image();
static void next_image(int n);


void imageset_ui_run(Imageset* is)
{
	imageset = is;

	if(utarray_len(is->images) > 0)
		image_selected = 0;

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
				click(e.button.x, e.button.y);
				break;
			case SDL_KEYDOWN:
				keypress(e.key.keysym.sym);
				break;
			}
		}
	}
}


static void click(int x, int y)
{
	int i;
	for(i=0; i<n_buttons; i++)
	{
		SDL_Rect r = buttons[i];
		if(x >= r.x && y >= r.y && x < r.x+r.w && y < r.y+r.h)
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
			case 3:
				edit_image();
				change_image(&n_buttons, &buttons);
				break;
			case 4:
				delete_image();
				change_image(&n_buttons, &buttons);
				break;
			default:
				abort();
			}
	}
}


static void keypress(SDLKey sym)
{
	if(sym == SDLK_n)
	{
		image_selected = new_image();
		change_image(&n_buttons, &buttons);
		return;
	}
	
	if(n_buttons > 1)
	{
		switch(sym)
		{
		case SDLK_LEFT:
			next_image(-1);
			break;
		case SDLK_RIGHT:
			next_image(1);
			break;
		case SDLK_RETURN:
			edit_image();
			change_image(&n_buttons, &buttons);
			break;
		case SDLK_DELETE:
			delete_image();
			change_image(&n_buttons, &buttons);
			break;
		case SDLK_s:
			imageset_save(imageset);
			break;
		default:
			break;
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

		Image* img = (Image*)utarray_eltptr(imageset->images, image_selected);
		SDL_Rect r = { screen->w/2 - img->sf->w/2,
			       screen->h/2 - img->sf->h/2 };
		SDL_BlitSurface(img->sf, NULL, screen, &r);
		print(10, 10, "Image %d", image_selected);
	}
	
	SDL_Flip(screen);
}


static int new_image()
{
	Image* img = imageset_add_image(imageset);
	editor_run(img);
	return utarray_len(imageset->images) - 1;
}


static void edit_image()
{
	Image* img = (Image*)utarray_eltptr(imageset->images, image_selected);
	editor_run(img);
}


static void delete_image()
{
	if(ask_yn("Are you sure you want to delete this image? [Y/N]"))
	{
		imageset_delete_image(imageset, image_selected);
		if(image_selected+1 > utarray_len(imageset->images))
			--image_selected;
		change_image(&n_buttons, &buttons);
	}
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
