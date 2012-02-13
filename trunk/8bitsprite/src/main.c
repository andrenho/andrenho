#include "SDL.h"
#include "SDL_ttf.h"

#include <stdio.h>

#include "util.h"

SDL_Surface* screen;
TTF_Font* font;

static int initialize_sdl();
static void print_title();
static void wait_for_keypress();

static char* title[] = {
"   __    __          __                              __             ",
" /'_ `\\ /\\ \\      __/\\ \\__                        __/\\ \\__          ",
"/\\ \\L\\ \\\\ \\ \\____/\\_\\ \\ ,_\\   ____  _____   _ __ /\\_\\ \\ ,_\\    __   ",
"\\/_> _ <_\\ \\ '__`\\/\\ \\ \\ \\/  /',__\\/\\ '__`\\/\\`'__\\/\\ \\ \\ \\/  /'__`\\ ",
"  /\\ \\L\\ \\\\ \\ \\L\\ \\ \\ \\ \\ \\_/\\__, `\\ \\ \\L\\ \\ \\ \\/ \\ \\ \\ \\ \\_/\\  __/ ",
"  \\ \\____/ \\ \\_,__/\\ \\_\\ \\__\\/\\____/\\ \\ ,__/\\ \\_\\  \\ \\_\\ \\__\\ \\____\\",
"   \\/___/   \\/___/  \\/_/\\/__/\\/___/  \\ \\ \\/  \\/_/   \\/_/\\/__/\\/____/", 
"                                      \\ \\_\\                         ",
"                                       \\/_/                         " , 0};


int main()
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
		fprintf(stderr, "Unable to open SDL video: %s\\n", SDL_GetError());
		return 0;
	}

	// initialize TTF
	if(TTF_Init())
	{
		fprintf(stderr, "Error on initializing TTF: %s\\n", TTF_GetError());
		return 0;
	}

	// load font
	if(!(font = TTF_OpenFont(DATADIR "/Pic0.ttf", 16)))
	{
		fprintf(stderr, "Error loading font: %s\\n", TTF_GetError());
		return 0;
	}

	return 1;
}


static void print_title()
{
	print(10, 10, "Teste");
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
				return 0;
			}
		}
}
