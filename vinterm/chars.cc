#include "chars.h"

#include "screen.h"

Chars::Chars(Options const& options, Font const& font)
	: options(options),
	  font(font),
	  chars(new SDL_Surface**[256])
{
	for(int i=0; i<256; i++)
	{
		chars[i] = new SDL_Surface*[NUM_ATTRS];
		chars[i][NORMAL] = CreateChar(i, NORMAL);
	}
}


Chars::~Chars()
{
	for(int i=0; i<256; i++)
	{
		for(int j=0; j<NUM_ATTRS; j++)
			SDL_FreeSurface(chars[i][NORMAL]);
		delete[] chars[i];
	}
	delete[] chars;
}


SDL_Surface* 
Chars::CreateChar(int c, CharAttr attr)
{
	SDL_Surface* s = SDL_CreateRGBSurface(SDL_SWSURFACE,
			(font.char_w+2) * options.scale, 
			(font.char_h+2) * options.scale,
			8, 0, 0, 0, 0);
	Screen::initializePalette(s, options);
	SDL_FillRect(s, NULL, 0);
	P(s, 2, 2) = 255;
	// TODO...

	return s;
}
