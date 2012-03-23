#include "chars.h"

#include "screen.h"
#include "filter.h"

Chars::Chars(Options const& options, Font const& font)
	: start_at_x(1), start_at_y(1),
	  options(options),
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
	// create surface
	SDL_Surface* s = SDL_CreateRGBSurface(SDL_SWSURFACE,
			(font.char_w+(2*start_at_x)) * options.scale, 
			(font.char_h+(2*start_at_y)) * options.scale,
			8, 0, 0, 0, 0);
	Screen::initializePalette(s, options);
	SDL_FillRect(s, NULL, 0);

	// copy char
	int color = 200; // TODO
	if(options.scale == 1)
		for(int x=0; x<font.char_w; x++)
			for(int y=0; y<font.char_h; y++)
				P(s, x + start_at_x, y + start_at_y) = 
					font.ch[c][y*font.char_w+x] ? color : 0;
	else
		for(int x=0; x<font.char_w; x++)
			for(int y=0; y<font.char_h; y++)
			{
				SDL_Rect r = {
					(x + start_at_x) * options.scale,
					(y + start_at_y) * options.scale,
					options.scale, options.scale };
				if(font.ch[c][y*font.char_w+x])
					SDL_FillRect(s, &r, color);
			}

	// apply filters
	vector<Filter*>::const_iterator filter;
	for(filter = options.PreFilters()->begin(); 
			filter < options.PreFilters()->end(); 
			filter++)
		(*filter)->Apply(s, options);

	return s;
}
