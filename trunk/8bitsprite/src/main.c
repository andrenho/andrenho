#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_image.h"

#include <stdio.h>
#include <stdlib.h>

#include "util.h"
#include "args.h"

SDL_Surface* screen;
TTF_Font* font;

static int initialize_sdl();
static void print_title();
static void wait_for_keypress();

int main(int argc, char* argv[])
{
	if(!initialize_sdl())
		return 1;
	
	print_title();
	wait_for_keypress();

	return 0;
}


static int initialize_sdl()
{
	// initialize SDL
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		fprintf(stderr, "Unable to initialize SDL: %s\\n", SDL_GetError());
		return 0;
	}

	// initialize video
	screen = SDL_SetVideoMode(640, 480, 8, SDL_SWSURFACE|SDL_RESIZABLE);
	if(!screen)
	{
		fprintf(stderr, "Unable to open SDL video: %s\n", SDL_GetError());
		return 0;
	}

	// initialize TTF
	if(TTF_Init())
	{
		fprintf(stderr, "Error on initializing TTF: %s\n", TTF_GetError());
		return 0;
	}

	// load font
	if(!(font = TTF_OpenFont(DATADIR "/Pic0.ttf", 16)))
	{
		fprintf(stderr, "Error loading font: %s\\n", TTF_GetError());
		return 0;
	}

	// initialize images
	if(IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG)
	{
		fprintf(stderr, "Error initializing IMG: %s\n", IMG_GetError());
		return 0;
	}

	return 1;
}


static void print_title()
{
	SDL_Surface *title = IMG_Load(DATADIR "/title.png");
	if(!title)
		abort();

	SDL_Rect r = { 10, 10, 0, 0 };
	SDL_BlitSurface(title, NULL, screen, &r);

	int y = 140;
	y = print(10, y, "Created by Andre' Wagner (2012)");
	y = print(10, y, "Licensed under the GPLv3. Please see COPYING file for details.");

	print(10, screen->h - 30, "Press any key to continue.");

	SDL_Flip(screen);
}


static void wait_for_keypress()
{
	SDL_Event e;
	while(1)
		while(SDL_WaitEvent(&e))
		{
			if(e.type == SDL_QUIT)
			{
				SDL_Quit();
				return;
			}
			else if(e.type == SDL_KEYDOWN || e.type == SDL_MOUSEBUTTONDOWN)
				return;
		}
}
