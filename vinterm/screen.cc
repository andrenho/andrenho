#include "screen.h"

#include <cstdlib>
#include "SDL.h"

Screen::Screen(Options const& options, Terminal const& terminal)
	: options(options), 
	  font(new Font()), 
	  chars(new Chars(options, *font)),
	  terminal(terminal), 
	  border_x(options.border_x * options.scale),
	  border_y(options.border_y * options.scale),
	  w(terminal.w * font->char_w * options.scale + (border_x * 2)), 
	  h(terminal.h * font->char_h * options.scale + (border_y * 2))
{
       	screen = SDL_SetVideoMode(w, h, 8, SDL_SWSURFACE);
	if(!screen)
	{
		fprintf(stderr, "It was not possible to open the display: %s\n",
				SDL_GetError());
		exit(1);
	}
	initializePalette(screen, options);
}


Screen::~Screen()
{
	delete font;
	delete chars;
}


void
Screen::initializePalette(SDL_Surface* sf, Options const& options)
{
	double rr = (options.bright_color.r - options.background_color.r) / 255.0;
	double rg = (options.bright_color.g - options.background_color.g) / 255.0;
	double rb = (options.bright_color.b - options.background_color.b) / 255.0;

	SDL_Color palette[256];
	for(double i=0; i<256; i++)
		palette[(Uint8)i] = (SDL_Color) {
			(Uint8)(options.background_color.r + (rr * i)),
			(Uint8)(options.background_color.g + (rg * i)),
			(Uint8)(options.background_color.b + (rb * i)) };
	SDL_SetColors(sf, palette, 0, 256);
}


void
Screen::UpdateFromTerminal()
{
	// TODO - make it faster
	
	/*
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
	*/
}


/*
void 
Screen::SetChar(const char c, const int x, const int y)
{
	// TODO - check borders
	for(int yy=0; yy<font->char_h; yy++)
		memcpy(&sf[(y*font->char_h+yy)*w+(x*font->char_w)],
		       &font->ch[(int)c][yy*font->char_w], 
		       font->char_w);

}
*/



void 
Screen::UpdateToScreen()
{
	SDL_Flip(screen);
}
