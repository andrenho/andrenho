#ifndef LIBS_SDL_SDLIMAGE_H
#define LIBS_SDL_SDLIMAGE_H

#include <string>
#include <png.h>

#include "libs/image.h"
#include "libs/rect.h"

struct SDL_Surface;

class SDLImage : public Image {
public:
	SDLImage(SDL_Surface* sf, bool must_free=true);
	SDLImage(int w, int h);
	SDLImage(std::string const& filename, Rect const& r);
	~SDLImage();

	inline void SetPixel(int x, int y, Color c);
	void Blit(Image const& image, Rect const& r) const;
	void Update();
	void FillBox(Color c);
	void FillBox(Rect r, Color c);
	void DrawLine(Point p1, Point p2, Color c, int w=1);

protected:
	struct SDL_Surface* sf;

private:
	const bool must_free;
	SDL_Surface* SurfaceFromPNGAlpha(Rect const& r, png_bytep* row_pointers, 
			int n_col, png_color* palette, 
			int n_transp, png_bytep trans, int x_width) const;
};

#endif
