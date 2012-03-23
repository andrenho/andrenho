#include "chars.h"

Chars::Chars(Options const& options, Font const& font)
	: options(options),
	  font(font),
	  chars(new TerminalChar[256])
{
	for(int i=0; i<256; i++)
	{
		chars[i].normal = SDL_CreateRGBSurface(SDL_SWSURFACE,
				(font.char_w+2) * options.scale, 
				(font.char_h+2) * options.scale,
				8, 0, 0, 0, 0);
	}
}
