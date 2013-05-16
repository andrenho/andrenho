#include <stdio.h>
#include <stdlib.h>

#include "SDL.h"

static SDL_Surface* video;

static void init_video()
{
	SDL_Init(SDL_INIT_VIDEO);
	video = SDL_SetVideoMode(800, 600, 8, SDL_SWSURFACE);
}


static void check_events()
{
	SDL_Event e;
	while(SDL_PollEvent(&e))
	{
		switch(e.type)
		{
		case SDL_QUIT:
			SDL_Quit();
			exit(0);
		}
	}
}


static void draw_board()
{
}


static void update_osc()
{
}


int main(int argc, char** argv)
{
	init_video();
	draw_board();

	while(1)
	{
		check_events();
		update_osc();
	}
}
