#ifndef LIBS_SDL_SDLFONT_H
#define LIBS_SDL_SDLFONT_H

#include <string>
#include "SDL_ttf.h"

#include "libs/font.h"

class SDLFont : public Font {
public:
	SDLFont(std::string const& filename, int size);
	~SDLFont();
private:
	TTF_Font* font;
};

#endif

