#ifndef CHARS_H
#define CHARS_H

#include "SDL.h"

#include "font.h"
#include "options.h"
#include "terminal.h"

class Chars
{
public:
	Chars(Options const& options, Font const& font);
	~Chars();

	SDL_Surface* Char(int c, CharAttr attr) const { return chars[c][attr]; }

	const int start_at_x, start_at_y;

private:
	SDL_Surface* CreateChar(int c, CharAttr attr);

	Options const& options;
	Font const& font;
	SDL_Surface*** chars;
};

#endif
