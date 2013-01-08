#ifndef LIBS_SDL_SDLIMAGE_H
#define LIBS_SDL_SDLIMAGE_H

#include <string>

#include "libs/image.h"
#include "libs/rect.h"

class SDLImage : public Image {
public:
	SDLImage(std::string const& filename, Rect const& r);
};

#endif
