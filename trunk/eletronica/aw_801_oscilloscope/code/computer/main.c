#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "SDL.h"

#define W 800
#define H 600

static SDL_Surface* scr;

static void init_video()
{
	SDL_Init(SDL_INIT_VIDEO);
	scr = SDL_SetVideoMode(W, H, 8, SDL_SWSURFACE);

	SDL_Color c[] = {
		{ 0x00, 0x00, 0x00 },
		{ 0x00, 0xff, 0x00 },
	};
	SDL_SetColors(scr, c, 0, 2);
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
	// window
	SDL_FillRect(scr, &((SDL_Rect){ 50, 50, H-100, H-100 }), 1);
	SDL_FillRect(scr, &((SDL_Rect){ 53, 53, H-106, H-106 }), 0);

	// horizontal lines
	for(int i=50, j=0; i<H-100; i += (H-150) / 11, j++)
	{
		if(j == 6)
			SDL_FillRect(scr, &((SDL_Rect){ 50, i, H-100, 2 }), 1);
		else
		{
			int x;
			for(x=50; x<H-50; x += 3)
				*((Uint8*)(scr->pixels + i * scr->pitch + x)) = 1;
		}
	}
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
		SDL_Flip(scr);
	}
}
