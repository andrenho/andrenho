#include "screen.h"

#include <cstdlib>
#include "SDL.h"

Screen::Screen(Options const& options, Terminal& terminal)
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
	set<int>::const_iterator n;
	for(n = terminal.dirty.begin(); n != terminal.dirty.end(); n++)
	{
		int x = (*n) % terminal.w;
		int y = (*n) / terminal.w;
		TerminalChar ch = terminal.Ch(x, y);
		int xx = (x * font->char_w * options.scale) + border_x 
			- (options.scale * chars->start_at_x);
		int yy = (y * font->char_h * options.scale) + border_y
			- (options.scale * chars->start_at_y);
		SDL_Rect r = { xx, yy };
		SDL_BlitSurface(chars->Char(ch.ch, ch.attr), NULL, screen, &r);
	}

	terminal.dirty.clear();
}


void 
Screen::UpdateToScreen()
{
	SDL_Flip(screen); // TODO
}
