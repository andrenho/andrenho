#include "libs/sdl/sdlimage.h"

#include <cstdlib>
#include <stdint.h>
#include <algorithm>
#include <png.h>
#include "SDL.h"

#include "util/logger.h"

SDLImage::SDLImage(SDL_Surface* sf, bool must_free)
	: Image(sf->w, sf->h), must_free(must_free)
{
	this->sf = sf;
}


SDLImage::SDLImage(int w, int h)
	: Image(w, h), must_free(true)
{
	SDL_Surface* sf2 = SDL_CreateRGBSurface(SDL_SWSURFACE, w, h, 32,
			0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000);
	sf = SDL_DisplayFormat(sf2);
	SDL_FreeSurface(sf2);
}


SDLImage::SDLImage(std::string const& filename, Rect const& r)
	: Image(r.w, r.h), must_free(true)
{
	int _x = r.x, _y = r.y, _w = r.w, _h = r.h;

	// open file
	FILE* f = fopen(filename.c_str(), "rb");
	if(!f)
		logger.Error(1, "Error opening " + filename + ".");

	// read PNG header
	uint8_t sig[8];
	(void) fread(sig, 1, 8, f);
	if(!png_check_sig(sig, 8))
		logger.Error(1, filename + ": not a valid PNG file.");
	
	// prepare
	png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, 
			NULL, NULL);
	if(!png_ptr)
		logger.Error(1, "Error loading " + filename + ".");
	png_infop info_ptr = png_create_info_struct(png_ptr);

	// handle logger.Errorors
	if(setjmp(png_jmpbuf(png_ptr)))
	{
		png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
		logger.Error(1, "something went wrong while reading " + filename);
	}

	// read PNG file info
	int color_type, w, h;
	png_init_io(png_ptr, f);
	png_set_sig_bytes(png_ptr, 8);
	png_read_info(png_ptr, info_ptr);
	h = png_get_image_height(png_ptr, info_ptr);
	w = png_get_image_width(png_ptr, info_ptr);
	// bitdepth = png_get_bit_depth(png_ptr, info_ptr);
	color_type = png_get_color_type(png_ptr, info_ptr);

	if(_w == 0)
	{
		_w = w - _x;
		_h = h - _y;
	}

	// check bounds
	if(_x < 0 || _y < 0 || _w < 0 || _h < 0)
		logger.Error(1, "Image " + filename + " bounds < 0");
	if(_x+_w > w || _y+_h > h)
		logger.Error(1, "Image " + filename + " rectange out of bounds");

	// get palette
	int num_trans = 0;
	png_bytep trans_alpha = NULL;
	int n_col = 0;
	png_color* palette = NULL;

	if(color_type == PNG_COLOR_TYPE_PALETTE)
	{
		// read palette
		png_color* p;
		png_get_PLTE(png_ptr, info_ptr, &p, &n_col);

		// copy colors
		palette = (png_color*)malloc(sizeof(png_color) * 256);
		memcpy(palette, p, sizeof(png_color) * 256);

		// get transparent color
		if(png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS))
			png_get_tRNS(png_ptr, info_ptr, &trans_alpha, &num_trans, NULL);
	}

	// read image data
	png_bytep* row_pointers = (png_bytep*)malloc(sizeof(png_bytep) * h);
	int y;
	int x_width = png_get_rowbytes(png_ptr, info_ptr) / w;
	for(y=0; y<h; y++)
		row_pointers[y] = (png_bytep)malloc(x_width * w);
	png_read_image(png_ptr, row_pointers);

	// create SDL surface
	sf = SurfaceFromPNGAlpha(r, row_pointers, n_col, palette, num_trans, 
			trans_alpha, x_width);
	
	// free stuff
	if(png_ptr && info_ptr)
		png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
	for(y=0; y<h; y++)
		free(row_pointers[y]);
	free(row_pointers);
	free(palette);
	
	fclose(f);
}


SDLImage::~SDLImage()
{
	if(must_free)
		SDL_FreeSurface(sf);
}


SDL_Surface* 
SDLImage::SurfaceFromPNGAlpha(Rect const& r, png_bytep* row_pointers, 
		int n_col, png_color* palette, 
		int n_transp, png_bytep trans, int x_width) const
{
	if(palette)
		logger.Error(1, "Sorry: palettized surfaces on alpha not supported.");

	SDL_Surface* sf = SDL_CreateRGBSurface(SDL_SWSURFACE, 
			r.w, r.h, 32, 
			0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000);
	int _y;
	for(_y=0; _y<r.h; _y++)
		memcpy(((char*)sf->pixels) + (_y*r.w*4), 
				&row_pointers[_y+r.y][r.x*x_width], 
				r.w * x_width);
	SDL_Surface* sf2 = SDL_DisplayFormatAlpha(sf);
	SDL_FreeSurface(sf);

	return sf2;
}


inline void 
SDLImage::SetPixel(int x, int y, Color c)
{
	SDL_PixelFormat *fmt = sf->format;
	Uint32 color = (c.r >> fmt->Rloss) << fmt->Rshift
		| (c.g >> fmt->Gloss) << fmt->Gshift
		| (c.b >> fmt->Bloss) << fmt->Bshift | fmt->Amask;
	Uint8 *p = (Uint8*)sf->pixels + (y * sf->pitch) + (x * 4);
	*(Uint32*)p = color;
}


void 
SDLImage::Blit(Image const& image) const
{
	const SDLImage* dest = (const SDLImage*)&image;
	SDL_BlitSurface(sf, NULL, dest->sf, NULL);
}


void 
SDLImage::Blit(Image const& image, Rect const& r) const
{
	SDL_Rect rect = { (Sint16)r.x, (Sint16)r.y, (Uint16)r.w, (Uint16)r.h };
	const SDLImage* dest = (const SDLImage*)&image;
	SDL_BlitSurface(sf, NULL, dest->sf, &rect);
}


void 
SDLImage::FillBox(Color c)
{
	Uint32 color = SDL_MapRGB(sf->format, c.r, c.g, c.b);
	SDL_FillRect(sf, NULL, color);
}


void 
SDLImage::FillBox(Rect r, Color c)
{
	SDL_Rect rect = { (Sint16)r.x, (Sint16)r.y, (Uint16)r.w, (Uint16)r.h };
	Uint32 color = SDL_MapRGB(sf->format, c.r, c.g, c.b);
	SDL_FillRect(sf, &rect, color);
}


void 
SDLImage::DrawLine(Point p1, Point p2, Color c, int line_width)
{
	int x0 = std::min(std::max(p1.x, 0), this->w - line_width),
	    y0 = std::min(std::max(p1.y, 0), this->h - line_width),
	    x1 = std::min(p2.x, this->w - line_width),
	    y1 = std::min(p2.y, this->h - line_width);
	Uint32 color = SDL_MapRGB(sf->format, c.r, c.g, c.b);
	int dx = abs(x1-x0), sx = x0<x1 ? 1 : -1;
	int dy = abs(y1-y0), sy = y0<y1 ? 1 : -1;
	int err = (dx>dy ? dx : -dy)/2, e2;

	for(;;)
	{
		int xx = 0; //rand() % w;
		int yy = 0; //rand() % w;
		for(int x=0; x<line_width; x++)
			for(int y=0; y<line_width; y++)
			{
				Uint8 *p = (Uint8*)sf->pixels 
						+ ((y0+y+yy) * sf->pitch)
						+ ((x0+x+xx) * 4);
				*(Uint32*)p = color;
			}
		if(x0 == x1 && y0 == y1)
			break;
		e2 = err;
		if(e2 > -dx)
		{
			err -= dy;
			x0 += sx;
		}
		if(e2 < dy)
		{
			err += dx;
			y0 += sy;
		}
	}
}


void 
SDLImage::Update()
{
	SDL_Flip(sf);
}
