#ifndef SCREEN_H
#define SCREEN_H

#include "SDL.h"

#include "filter.h"
#include "options.h"
#include "terminal.h"

#define P(sf,x,y) *((Uint8*)(sf)->pixels + (y)*(sf)->pitch + (x))

class Screen
{
public:
	Screen(Options const& options, Terminal const& terminal);
	void ApplyFilter(Filter const& filter);
	void UpdateFromTerminal();
	void UpdateToScreen();

private:
	void initializePalette();

	Options const& options;
	Terminal const& terminal;
	const int w, h;
	SDL_Surface* screen;
};

#endif
