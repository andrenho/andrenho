#include "resource.h"

#include <setjmp.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include <png.h>
#include "SDL.h"

#include "ui/ui.h"
#include "util/log.h"
#include "util/strings.h"
#include "util/uthash.h"

// record for the resource hash
typedef struct SurfaceResource {
	char name[20];
	SDL_Surface* sf;
	struct UT_hash_handle hh;
} SurfaceResource;
static SurfaceResource* resources = NULL;  // resource hash

// resource files list
static struct { 
	char *name, *filename;
	int x, y, w, h;
} reslist[] = {
	{ "grassm", "grass.png", 96, 32, 32, 32 },
	{ NULL, NULL, 0, 0, 0, 0 }
};

// palette
SDL_Color colors[256];
int n_colors = 0;

// prototypes
static char* resource_find_file(char* filename);
static SDL_Surface* resource_load_png(char* filename, int x, int y, int _w, int _h);
static SDL_Surface* resource_sf_from_png(int w, int h, png_bytep* row_pointers,
		 int n_col, png_color* palette, int trans);
char *strdup (const char *str);  // silly mingw


int resources_load(UI* ui)
{
	// initialize colors
	int i;
	for(i=0; i<256; i++)
		colors[i] = (SDL_Color){ 0, 0, 0 };
	colors[WHITE] = (SDL_Color){ 255, 255, 255 };
	n_colors = 2;

	// load resources
	i = 0;
	while(reslist[i].name)
	{
		// find file
		char* filepath = resource_find_file(reslist[i].filename);
		if(!filepath)
			errx(1, "Could not find file %s.", reslist[i].filename);

		// load image
		SDL_Surface* sf = NULL;
		if(endswith(reslist[i].filename, ".png"))
			sf = resource_load_png(filepath, reslist[i].x, reslist[i].y,
					                 reslist[i].w, reslist[i].h);
		else
		{
			errx(1, "Invalid file type %s.", filepath);
			return 0;
		}

		free(filepath);

		// verify
		if(!sf)
		{
			errx(1, "Error loading resource %s.", 
					reslist[i].filename);
			return 0;
		}

		// add to hash
		SurfaceResource* res = malloc(sizeof(SurfaceResource));
		strncpy(res->name, reslist[i].name, 20);
		res->name[19] = 0;
		res->sf = sf;
		HASH_ADD_STR(resources, name, res);

		++i;
	}

	// set palette
	SurfaceResource *res, *tmp;
	HASH_ITER(hh, resources, res, tmp)
		SDL_SetColors(res->sf, colors, 0, n_colors);
	SDL_SetColors(ui->screen, colors, 0, n_colors);

	return 1;
}


void resources_unload(UI* ui)
{
	struct SurfaceResource *res, *tmp;
	HASH_ITER(hh, resources, res, tmp)
	{
		HASH_DEL(resources, res);
		if(res->sf)
			SDL_FreeSurface(res->sf);
		free(res);
	}
}


SDL_Surface* res(const char* name)
{
	SurfaceResource *rs;
	HASH_FIND_STR(resources, name, rs);
	if(!rs)
		errx(1, "Could not find resource %s.", name);
	return rs->sf;
}

/*
 * STATIC
 */


static char* resource_find_file(char* filename)
{
	const int MAX_BUF = 2;
	char buf[MAX_BUF][1024];
	snprintf(buf[0], 1023, DATADIR "/%s", filename); // data dir
	snprintf(buf[1], 1023, "data/%s", filename); // runs without install

	int i;
	for(i=0; i<MAX_BUF; i++)
	{
		struct stat b;
		if(stat(buf[i], &b) == 0)
			return strdup(buf[i]);
	}

	return NULL;
}


static SDL_Surface* resource_load_png(char* filename, int _x, int _y, int _w, int _h)
{
	// open file
	FILE* f = fopen(filename, "rb");
	if(!f)
		err(1, "Error opening %s.", filename);

	// read PNG header
	uint8_t sig[8];
	(void) fread(sig, 1, 8, f);
	if(!png_check_sig(sig, 8))
		errx(1, "%s: not a valid PNG file.\n", filename);
	
	// prepare
	png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, 
			NULL, NULL);
	if(!png_ptr)
		err(1, "Error loading %s.", filename);
	png_infop info_ptr = png_create_info_struct(png_ptr);

	// handle errors
	if(setjmp(png_jmpbuf(png_ptr)))
	{
		png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
		errx(1, "something went wrong while reading %s", filename);
	}

	// read PNG file info
	int bitdepth, color_type, w, h;
	png_init_io(png_ptr, f);
	png_set_sig_bytes(png_ptr, 8);
	png_read_info(png_ptr, info_ptr);
	h = png_get_image_height(png_ptr, info_ptr);
	w = png_get_image_width(png_ptr, info_ptr);
	bitdepth = png_get_bit_depth(png_ptr, info_ptr);
	color_type = png_get_color_type(png_ptr, info_ptr);
	if(color_type != PNG_COLOR_TYPE_PALETTE || bitdepth != 8)
	{
		png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
		errx(1, "%s: only 8-bit paletted images are supported.\n",
			       	filename);
	}

	// read palette
	png_color* p;
	int n_col;
	png_get_PLTE(png_ptr, info_ptr, &p, &n_col);

	// copy colors
	png_color* palette = malloc(sizeof(png_color) * 256);
	memcpy(palette, p, sizeof(png_color) * 256);

	// get transparent color
	int transparent = -1;
	if(png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS))
	{
		png_bytep trans_alpha;
		int num_trans;
		png_get_tRNS(png_ptr, info_ptr, &trans_alpha, &num_trans, NULL);
		if(num_trans > 0)
			transparent = trans_alpha[0];
	}

	// TODO - check bounds

	// read image data
	// TODO - get only the selected part of the image
	png_bytep* row_pointers = malloc(sizeof(png_bytep) * h);
	int y;
	for(y=0; y<h; y++)
		row_pointers[y] = malloc(png_get_rowbytes(png_ptr, info_ptr));
	png_read_image(png_ptr, row_pointers);

	// create SDL surface
	SDL_Surface* sf = resource_sf_from_png(w, h, row_pointers, 
			                       n_col, palette, transparent);
	
	// free stuff
	if(png_ptr && info_ptr)
		png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
	for(y=0; y<h; y++)
		free(row_pointers[y]);
	free(row_pointers);
	free(palette);
	
	fclose(f);

	debug("%s loaded.", filename);

	return sf;
}


static SDL_Surface* resource_sf_from_png(int w, int h, png_bytep* row_pointers,
		int n_col, png_color* palette, int transp)
{
	SDL_Surface* sf = SDL_CreateRGBSurface(SDL_SWSURFACE, w, h, 8, 
			                       0, 0, 0, 0);

	int x, y;
	for(x=0; x<w; x++)
		for(y=0; y<h; y++)
		{
			int c_sdl = -1;

			// get pixel color
			int c_px = row_pointers[y][x];
			png_color c = palette[c_px];

			// find color on the palette
			int j;
			for(j=0; j<n_colors; j++)
				if(colors[j].r == c.red && colors[j].g == c.green
						&& colors[j].b == c.blue)
				{
					c_sdl = j;
					break;
				}
		
			// color not found - add to palette
			if(c_sdl == -1)
			{
				colors[n_colors] = (SDL_Color){ c.red, c.green, 
					c.blue };
				++n_colors;
			}
	
			// draw pixel
			((char*)sf->pixels)[x + (y*w)] = c_sdl;
		}

	// TODO - transparency

	return sf;
}
