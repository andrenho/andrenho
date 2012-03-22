#include "terminal.h"

#include "SDL.h"

Terminal::Terminal(Options const& options)
	: font(new Font()), options(options), 
	  w(options.w*font->char_w), h(options.h*font->char_h),
	  sf(new uint8_t[w*h])
{
	for(int i=0; i<(w*h); i++)
		sf[i] = 0;
	for(char c='A', i=0; c<='z'; c++, i++)
		SetChar(c, i, 0);
}

Terminal::~Terminal()
{
	delete font;
	delete[] sf;
}

void 
Terminal::SetChar(const char c, const int x, const int y)
{
	// TODO - check borders
	for(int yy=0; yy<font->char_h; yy++)
		memcpy(&sf[(y*font->char_h+yy)*w+(x*font->char_w)],
		       &font->ch[(int)c][yy*font->char_w], 
		       font->char_w);
}


bool
Terminal::Process()
{
	SDL_Event e;
	while(SDL_PollEvent(&e))
	{
		switch(e.type)
		{
		case SDL_QUIT:
			return false;
		}
	}
	return true;
}
