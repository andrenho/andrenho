#ifndef LIBS_SDL_SDLFONT_H
#define LIBS_SDL_SDLFONT_H

#include <string>

#include "libs/font.h"
#include "util/defines.h"

struct _TTF_Font;

class SDLFont : public Font {
public:
	SDLFont(const std::string& filename, int size);
	~SDLFont();
private:
	struct _TTF_Font* font;

	DISALLOW_COPY_AND_ASSIGN(SDLFont);
};

#endif

