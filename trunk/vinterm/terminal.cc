#include "terminal.h"

#include "SDL.h"

Terminal::Terminal(Options const& options)
	: w(80), h(25), options(options)
{
	/*
	for(char c='A', i=0; c<='z'; c++, i++)
	{
		SetChar(c, i, 0);
		SetChar(c, i, 1);
	}
	SetChar('@', 79, 24);
	*/
}


Terminal::~Terminal()
{
}


void 
Terminal::SetChar(const char c, const int x, const int y)
{
	// TODO
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
