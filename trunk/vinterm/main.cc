#include <vector>
#include "SDL.h"
using namespace std;

#include "filter.h"
#include "filter_inexact.h"
#include "options.h"
#include "screen.h"
#include "terminal.h"

int main(int argc, char* argv[])
{
	if(SDL_Init(SDL_INIT_VIDEO) == -1)
	{
		fprintf(stderr, "Error opening SDL: %s.", SDL_GetError());
		return 1;
	}

	Options options;
	Terminal terminal(options);
	Screen screen(options, terminal);

	bool i = true;
	while(1)
	{
		terminal.BeginFrame();
		if(!terminal.Process())
			break;

		if(i)
		{
			screen.UpdateFromTerminal();

			vector<Filter*>::const_iterator filter;
			for(filter = options.Filters()->begin(); 
					filter < options.Filters()->end(); 
					filter++)
				(*filter)->Apply(screen, options);
			
			screen.UpdateToScreen();
			i = false;
		}

		terminal.EndFrame();
	}

	SDL_Quit();
	return 0;
}
