#include "libs/sdl/sdl.h"

using namespace std;

#include "util/logger.h"
#include "libs/sdl/sdlfont.h"
#include "libs/sdl/sdlimage.h"
#include "libs/sdl/sdltimer.h"

#include "SDL_ttf.h"

SDL::SDL()
{
	// initialize SDL
	if((SDL_Init(SDL_INIT_VIDEO)) != 0)
		logger.Error(2, "Could not initialize SDL: %s.", 
				SDL_GetError());
	logger.Debug("SDL initialized.");

	// create window
	screen = SDL_SetVideoMode(800, 600, 32, SDL_SWSURFACE|SDL_RESIZABLE);
	//screen = SDL_SetVideoMode(0, 0, 32, SDL_HWSURFACE|SDL_FULLSCREEN|SDL_DOUBLEBUF);
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


Image* 
SDL::CreateImage(int w, int h) const
{
	SDLImage* img(new SDLImage(w, h));
	return img;
}


Image*
SDL::LoadImage(const string& filename, const Rect& r) const
{
	SDLImage* img(new SDLImage(filename, r));
	return img;
}


Font* 
SDL::LoadFont(const string& filename, int size) const
{
	SDLFont* font(new SDLFont(filename, size));
	return font;
}


const Event* 
SDL::GetEvent() const
{
	SDL_Event e = { };
	if(!SDL_PollEvent(&e))
		return new Event(Event::NO_EVENT);
	switch(e.type) {
		case SDL_QUIT:
			return new Event(Event::QUIT);
		case SDL_KEYDOWN:
		{
			int key;
			switch(e.key.keysym.sym) {
			case SDLK_UP:
				key = Key::UP; break;
			case SDLK_DOWN:
				key = Key::DOWN; break;
			case SDLK_LEFT:
				key = Key::LEFT; break;
			case SDLK_RIGHT:
				key = Key::RIGHT; break;
			default:
				key = e.key.keysym.sym;
			}
			return new KeyEvent(key);
		}
			break;
		case SDL_MOUSEBUTTONDOWN:
		{
			ClickEvent::MouseButton b(ClickEvent::LEFT);
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


Timer* 
SDL::CreateTimer(int wait_ms) const 
{ 
	SDLTimer* timer(new SDLTimer(wait_ms));
	return timer;
}


void 
SDL::GetKeyState(KeyState& state) const
{
	SDL_PumpEvents();
	SDLMod mod(SDL_GetModState());
	Uint8 *k(SDL_GetKeyState(NULL));

	state.Shift = mod & KMOD_SHIFT;
	state.Control = mod & KMOD_CTRL;

	state.Left  = k[SDLK_LEFT];
	state.Right = k[SDLK_RIGHT];
	state.Up    = k[SDLK_UP];
	state.Down  = k[SDLK_DOWN];
}
