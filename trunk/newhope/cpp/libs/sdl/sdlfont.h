#ifndef LIBS_SDL_SDLFONT_H
#define LIBS_SDL_SDLFONT_H

#include <string>

#include "libs/font.h"

struct _TTF_Font;

class SDLFont : public Font {
public:
	SDLFont(std::string const& filename, int size);
	~SDLFont();
private:
	struct _TTF_Font* font;
};

#endif

