#include "libs/sdl/sdl.h"

#include "SDL_ttf.h"

#include "util/logger.h"
#include "libs/sdl/sdlfont.h"
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
	Window = new SDLImage(screen, false);
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
	delete Window;
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
SDL::ReachedCountDown() const
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
SDL::CreateImage(int w, int h) const
{
	SDLImage* img = new SDLImage(w, h);
	return *img;
}


Image&
SDL::LoadImage(std::string const& filename, Rect const& r) const
{
	SDLImage* img = new SDLImage(filename, r);
	return *img;
}


Font& 
SDL::LoadFont(std::string const& filename, int size) const
{
	SDLFont* font = new SDLFont(filename, size);
	return *font;
}


Event const* 
SDL::GetEvent() const
{
	SDL_Event e;
	SDL_PollEvent(&e);
	switch(e.type)
	{
		case SDL_QUIT:
			return new Event(Event::QUIT);
		case SDL_KEYDOWN:
			return new KeyEvent(e.key.keysym.sym);
		case SDL_MOUSEBUTTONDOWN:
		{
			ClickEvent::MouseButton b = ClickEvent::LEFT;
			if(e.button.button == SDL_BUTTON_RIGHT)
				b = ClickEvent::RIGHT;
			else if(e.button.button == SDL_BUTTON_MIDDLE)
				b = ClickEvent::MIDDLE;
			return new ClickEvent(e.button.x, e.button.y, b);
		}
		case SDL_VIDEORESIZE:
			screen = SDL_SetVideoMode(e.resize.w, e.resize.h, 32, 
				SDL_SWSURFACE|SDL_RESIZABLE);
			delete Window;
			Window = new SDLImage(screen, false);
			return new Event(Event::RESIZE);
	}
	return new Event(Event::NO_EVENT);
}
