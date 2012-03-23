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

	while(1)
	{
		if(!terminal.Process())
			break;
		screen.Update();
	}

	SDL_Quit();
	return 0;
}
