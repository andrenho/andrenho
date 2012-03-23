#ifndef CHARS_H
#define CHARS_H

#include "SDL.h"

#include "font.h"
#include "options.h"

typedef struct TerminalChar
{
	SDL_Surface *normal;
};

class Chars
{
public:
	Chars(Options const& options, Font const& font);
	~Chars() { delete[] chars; }

private:
	Options const& options;
	Font const& font;
	TerminalChar* chars;
};

#endif
