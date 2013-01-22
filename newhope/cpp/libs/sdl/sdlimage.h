#ifndef LIBS_SDL_SDLIMAGE_H
#define LIBS_SDL_SDLIMAGE_H

#include <string>
#include <png.h>

#include "SDL.h"

#include "libs/image.h"
#include "util/rect.h"
#include "util/defines.h"

struct SDL_Surface;

class SDLImage : public Image {
public:
	SDLImage(int w, int h); // create blank surface
	explicit SDLImage(SDL_Surface* sf, bool must_free=true);
	SDLImage(std::string const& filename, Rect const& r);
	~SDLImage();

	void Blit(Image const& image) const;
	void Blit(Image const& image, Rect const& r) const;
	void Update();
	void FillBox(Color c);
	void FillBox(Rect r, Color c);
	void DrawLine(IPoint p1, IPoint p2, Color c, int w=1);

	inline void SetPixel(int x, int y, Color c)
	{
		SDL_PixelFormat *fmt = sf->format;
		Uint32 color = (c.r >> fmt->Rloss) << fmt->Rshift
			| (c.g >> fmt->Gloss) << fmt->Gshift
			| (c.b >> fmt->Bloss) << fmt->Bshift | fmt->Amask;
		Uint8 *p = (Uint8*)sf->pixels + (y * sf->pitch) + (x * 4);
		*(Uint32*)p = color;
	}

protected:
	struct SDL_Surface* sf;

private:
	const bool must_free;
	SDL_Surface* SurfaceFromPNGAlpha(Rect const& r, png_bytep* row_pointers, 
			int n_col, png_color* palette, 
			int n_transp, png_bytep trans, int x_width) const;

	DISALLOW_COPY_AND_ASSIGN(SDLImage);
};

#endif
