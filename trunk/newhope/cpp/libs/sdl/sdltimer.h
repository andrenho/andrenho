#ifndef LIBS_SDL_SDLTIMER_H
#define LIBS_SDL_SDLTIMER_H

#include "libs/graphiclibrary.h"
#include "util/defines.h"
#include "SDL.h"

class SDLTimer : public Timer {
public:
	explicit SDLTimer(int wait_ms)
		: Timer(wait_ms), countdown(SDL_GetTicks() + wait_ms) { }

	inline bool ReachedCountDown() const { 
		return SDL_GetTicks() >= countdown; 
	}

	inline void WaitCountDown() {
		while(SDL_GetTicks() < countdown) 
			SDL_Delay(1);
	}

private:
	const uint32_t countdown;

	DISALLOW_COPY_AND_ASSIGN(SDLTimer);
};

#endif
