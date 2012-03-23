#include "terminal.h"

#include "SDL.h"

Terminal::Terminal(Options const& options)
	: w(80), h(25), options(options), ch(new TerminalChar*[w])
{
	for(int x=0; x<w; x++)
		ch[x] = new TerminalChar[h];
}


Terminal::~Terminal()
{
	for(int x=0; x<w; x++)
		delete[] ch[x];
	delete[] ch;
	dirty.clear();
}


void 
Terminal::SetChar(const int x, const int y, char c, CharAttr attr)
{
	// TODO - check bounds
	ch[x][y].ch = c;
	ch[x][y].attr = attr;
	dirty.insert(y*w+x);
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
