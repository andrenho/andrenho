#include "libs/sdl/sdltimer.h"

#include "SDL.h"

SDLTimer::SDLTimer(int wait_ms)
	: Timer(wait_ms), countdown(SDL_GetTicks() + wait_ms) 
{ 
}


bool 
SDLTimer::ReachedCountDown() const 
{ 
	return SDL_GetTicks() >= countdown; 
}


void 
SDLTimer::WaitCountDown() 
{ 
	while(SDL_GetTicks() < countdown) 
		SDL_Delay(1); 
}
