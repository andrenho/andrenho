#include "terminal.h"

#include "SDL.h"

Terminal::Terminal(Options const& options)
	: options(options), sf(new uint8_t[options.pw * options.ph]),
	  w(options.pw), h(options.ph)
{
	for(int i=0; i<(options.pw * options.ph); i++)
		sf[i] = 0;
	sf[100*400+100] = 2;
}


void
Terminal::Process()
{
	SDL_Event e;
	while(SDL_PollEvent(&e))
	{
		switch(e.type)
		{
		case SDL_QUIT:
			SDL_Quit();
			exit(0);
		}
	}
}
