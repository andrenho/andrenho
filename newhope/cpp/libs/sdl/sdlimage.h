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
	SDLImage(const std::string& filename, const Rect& r);
	~SDLImage();

	void Blit(const Image& image) const;
	void Blit(const Image& image, const Rect& r) const;
	void Update();
	void FillBox(Color c);
	void FillBox(Rect r, Color c);
	void DrawLine(Point<int> p1, Point<int> p2, Color c, int w=1);

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
	SDL_Surface* SurfaceFromPNGAlpha(const Rect& r, png_bytep* row_pointers, 
			int n_col, png_color* palette, 
			int n_transp, png_bytep trans, int x_width) const;

	DISALLOW_COPY_AND_ASSIGN(SDLImage);
};

#endif
