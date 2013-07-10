#include "tilegame.h"

#include "SDL.h"

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Surface* screen = SDL_SetVideoMode(400, 300, 32, SDL_SWSURFACE);

	TG_Init(NULL, 8, 8);

	return 0;
}
