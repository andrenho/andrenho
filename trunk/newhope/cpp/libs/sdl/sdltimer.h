#ifndef LIBS_SDL_SDLTIMER_H
#define LIBS_SDL_SDLTIMER_H

#include "libs/graphiclibrary.h"

class SDLTimer : public Timer {
public:
	SDLTimer(int wait_ms);
	bool ReachedCountDown() const;
	void WaitCountDown();

private:
	const uint32_t countdown;
};

#endif
