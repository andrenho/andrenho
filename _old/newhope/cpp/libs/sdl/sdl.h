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
	Image* LoadImage(const std::string& filename, const Rect& r) const;
	Font* LoadFont(const std::string& filename, int size) const;

	const Event* GetEvent() const;
	void GetKeyState(KeyState& state) const;

private:
	mutable struct SDL_Surface* screen;

	DISALLOW_COPY_AND_ASSIGN(SDL);
};

#endif
