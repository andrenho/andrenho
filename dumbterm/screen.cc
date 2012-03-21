#include "screen.h"

#include <cstdlib>
#include "SDL.h"

Screen::Screen(Options const& options, Terminal const& terminal)
	: options(options), terminal(terminal), w(options.pw * options.scale),
	  h(options.ph * options.scale)
{
       	screen = SDL_SetVideoMode(w, h, 8, SDL_SWSURFACE);
	if(!screen)
	{
		fprintf(stderr, "It was not possible to open the display: %s\n",
				SDL_GetError());
		exit(1);
	}
	initializePalette();
}


void
Screen::initializePalette()
{
	SDL_Color palette[256];
	palette[0] = (SDL_Color) { 0, 0, 0 };
	// TODO
	palette[255] = (SDL_Color) { 104, 255, 159 };
	SDL_SetColors(screen, palette, 0, 256);
}


void 
Screen::ApplyFilter(Filter const& filter)
{
}


void
Screen::UpdateFromTerminal()
{
	const int sc = options.scale;
	for(int x=0; x<options.pw; x++)
		for(int y=0; y<options.ph; y++)
			for(int i=0; i<options.scale; i++)
				for(int j=0; j<options.scale; j++)
					P(screen, x*sc+i, y*sc+j) = 
							terminal.T(x, y);
}


void 
Screen::UpdateToScreen()
{
	SDL_Flip(screen);
}
