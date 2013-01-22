#ifndef LIBS_SDL_SDL_H
#define LIBS_SDL_SDL_H

#include <cstdint>
#include "libs/graphiclibrary.h"
#include "util/defines.h"

struct SDL_Surface;

class SDL : public GraphicLibrary {
public:
	SDL();
	~SDL();

	Timer* CreateTimer(int wait_ms) const;

	Image* CreateImage(int w, int h) const;
	Image* LoadImage(std::string const& filename, Rect const& r) const;
	Font* LoadFont(std::string const& filename, int size) const;

	Event const* GetEvent() const;
	void GetKeyState(KeyState& state) const;

private:
	mutable struct SDL_Surface* screen;

	DISALLOW_COPY_AND_ASSIGN(SDL);
};

#endif
