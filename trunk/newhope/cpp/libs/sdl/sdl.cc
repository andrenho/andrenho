#include "libs/sdl/sdl.h"

#include "SDL_ttf.h"

#include "util/logger.h"
#include "libs/sdl/sdlimage.h"

SDL::SDL()
	: countdown(0)
{
	// initialize SDL
	if((SDL_Init(SDL_INIT_VIDEO)) != 0)
		logger.Error(2, "Could not initialize SDL: %s.", 
				SDL_GetError());
	logger.Debug("SDL initialized.");

	// create window
	screen = SDL_SetVideoMode(0, 0, 32, SDL_SWSURFACE|SDL_RESIZABLE);
	if(!screen)
		logger.Error(2, "Could not initialize screen: %s.", 
				SDL_GetError());
	logger.Debug("SDL window initialized.");

	// setup window
	SDL_WM_SetCaption("New Hope (version " VERSION ")", "New Hope");
	SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, 
			SDL_DEFAULT_REPEAT_INTERVAL);

	// intialize SDL_ttf
	if(TTF_Init() == -1)
		logger.Error(2, "TTf_Init: %s", TTF_GetError());
}


SDL::~SDL()
{
	TTF_Quit();
	SDL_Quit();
	logger.Debug("SDL terminated.");
}


void 
SDL::StartCountDown(int wait_ms)
{
	countdown = SDL_GetTicks() + wait_ms;
}


bool 
SDL::ReachedCountDown()
{
	return SDL_GetTicks() >= countdown;
}


void 
SDL::WaitCountDown()
{
	while(SDL_GetTicks() < countdown)
		SDL_Delay(1);
}


Image&
SDL::LoadImage(std::string const& filename, Rect const& r) const
{
	SDLImage* img = new SDLImage(filename, r);
	return *img;
}
