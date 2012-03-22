#include "screen.h"

#include <cstdlib>
#include "SDL.h"

const SDL_Color Screen::BACKGROUND = (SDL_Color) { 30, 30, 30 };
const SDL_Color Screen::BRIGHT = (SDL_Color) { 140, 255, 190 };

Screen::Screen(Options const& options, Terminal const& terminal)
	: options(options), terminal(terminal), 
	  border_x(options.border_x * options.scale),
	  border_y(options.border_y * options.scale),
	  w(terminal.w * options.scale + (border_x * 2)), 
	  h(terminal.h * options.scale + (border_y * 2))
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


Screen::~Screen()
{
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
Screen::UpdateFromTerminal()
{
	// TODO - make it faster
	
	const int sc = options.scale;
	for(int x=0; x<terminal.w; x++)
		for(int y=0; y<terminal.h; y++)
			for(int i=0; i<options.scale; i++)
				for(int j=0; j<options.scale; j++)
				{
					uint8_t c;
					switch(terminal.T(x, y))
					{
						case 0: c =   0; break;
						case 1: c = 100; break;
						case 2: c = 200; break;
						case 3: c = 255; break;
					}
					P(screen, x*sc+i+border_x, y*sc+j+border_y) = c;
				}
}


void 
Screen::UpdateToScreen()
{
	SDL_Flip(screen);
}
