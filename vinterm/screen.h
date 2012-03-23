#ifndef SCREEN_H
#define SCREEN_H

#include "SDL.h"

#include "options.h"
#include "terminal.h"
#include "chars.h"

#define P(sf,x,y) *((Uint8*)(sf)->pixels + (y)*(sf)->pitch + (x))

class Screen
{
public:
	Screen(Options const& options, Terminal const& terminal);
	~Screen();

	void UpdateFromTerminal();
	void UpdateToScreen();

	SDL_Surface* ScreenSurface() const { return screen; }

private:
	static void initializePalette(SDL_Surface* sf, Options const& options);
	void initializeChars();

	Options const& options;
	const Font* const font;
	Chars* chars;
	Terminal const& terminal;
	const int border_x, border_y;
	const int w, h;
	SDL_Surface* screen;
};

#endif
