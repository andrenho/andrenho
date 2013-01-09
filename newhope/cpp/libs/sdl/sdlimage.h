#ifndef LIBS_SDL_SDLIMAGE_H
#define LIBS_SDL_SDLIMAGE_H

#include <string>
#include <png.h>

#include "libs/image.h"
#include "libs/rect.h"

struct SDL_Surface;

class SDLImage : public Image {
public:
	SDLImage(SDL_Surface* sf);
	SDLImage(int w, int h);
	SDLImage(std::string const& filename, Rect const& r);
	~SDLImage();

	inline void SetPixel(int x, int y, Color c);
	void Blit(Image const& image, Rect const& r);
	void Update();

protected:
	struct SDL_Surface* sf;

private:
	SDL_Surface* SurfaceFromPNGAlpha(Rect const& r, png_bytep* row_pointers, 
			int n_col, png_color* palette, 
			int n_transp, png_bytep trans, int x_width) const;
};

#endif
