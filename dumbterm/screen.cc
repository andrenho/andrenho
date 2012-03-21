#include "screen.h"

#include <cstdlib>
#include "SDL.h"

const SDL_Color Screen::BACKGROUND = (SDL_Color) { 30, 30, 30 };
const SDL_Color Screen::BRIGHT = (SDL_Color) { 120, 255, 170 };

Screen::Screen(Options const& options, Terminal const& terminal)
	: options(options), terminal(terminal), w(terminal.w * options.scale),
	  h(terminal.h * options.scale)
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
	double rr = (BRIGHT.r - BACKGROUND.r) / 255.0;
	double rg = (BRIGHT.g - BACKGROUND.g) / 255.0;
	double rb = (BRIGHT.b - BACKGROUND.b) / 255.0;

	SDL_Color palette[256];
	for(double i=0; i<256; i++)
		palette[(Uint8)i] = (SDL_Color) {
			(Uint8)(BACKGROUND.r + (rr * i)),
			(Uint8)(BACKGROUND.g + (rg * i)),
			(Uint8)(BACKGROUND.b + (rb * i)) };
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
	for(int x=0; x<terminal.w; x++)
		for(int y=0; y<terminal.h; y++)
			for(int i=0; i<options.scale; i++)
				for(int j=0; j<options.scale; j++)
					switch(terminal.T(x, y))
					{
					case 0:
						P(screen, x*sc+i, y*sc+j) = 0;
						break;
					case 1:
						P(screen, x*sc+i, y*sc+j) = 0;
						break;
					case 2:
						P(screen, x*sc+i, y*sc+j) = 255;
						break;
					case 3:
						P(screen, x*sc+i, y*sc+j) = 255;
						break;
					default:
						abort();
					}
}


void 
Screen::UpdateToScreen()
{
	SDL_Flip(screen);
}
