#ifndef LIBS_SDL_SDLIMAGE_H
#define LIBS_SDL_SDLIMAGE_H

#include <string>
#include <png.h>

#include "libs/image.h"
#include "libs/rect.h"

struct SDL_Surface;

class SDLImage : public Image {
public:
	SDLImage(std::string const& filename, Rect const& r);
	~SDLImage();
private:
	SDL_Surface* SurfaceFromPNGAlpha(Rect const& r, png_bytep* row_pointers, 
			int n_col, png_color* palette, 
			int n_transp, png_bytep trans, int x_width) const;

	struct SDL_Surface* sf;
};

#endif
