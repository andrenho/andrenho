#ifndef LIBS_SDL_SDL_H
#define LIBS_SDL_SDL_H

#include <cstdint>
#include "libs/graphiclibrary.h"

struct SDL_Surface;

class SDL : public GraphicLibrary {
public:
	SDL();
	~SDL();

	void StartCountDown(int wait_ms);
	bool ReachedCountDown() const;
	void WaitCountDown();

	Image* CreateImage(int w, int h) const;
	Image* LoadImage(std::string const& filename, Rect const& r) const;
	Font* LoadFont(std::string const& filename, int size) const;

	Event const* GetEvent() const;

	mutable struct SDL_Surface* screen;

private:
	uint32_t countdown;
};

#endif
