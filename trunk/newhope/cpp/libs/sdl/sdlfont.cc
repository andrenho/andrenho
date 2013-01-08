#include "libs/sdl/sdlfont.h"

#include "SDL_ttf.h"

#include "util/logger.h"

SDLFont::SDLFont(std::string const& filename, int size)
{
	font = TTF_OpenFont(filename.c_str(), size);
	if(!font)
		logger.Warning("TTF_OpenFont: %s", TTF_GetError());
}


SDLFont::~SDLFont()
{
	TTF_CloseFont(font);
}
