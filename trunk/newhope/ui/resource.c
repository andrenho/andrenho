#include "resource.h"

#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include <png.h>
#include "SDL.h"

#include "ui/ui.h"
#include "util/log.h"
#include "util/strings.h"
#include "util/uthash.h"

typedef struct SurfaceResource {
	char name[20];
	SDL_Surface* sf;
	struct UT_hash_handle hh;
} SurfaceResource;
static SurfaceResource* resources = NULL;

static struct { 
	char *name, *filename;
	int x, y, w, h;
} reslist[] = {
	{ "grassm", "grass.png", 96, 32, 32, 32 },
	{ NULL, NULL, 0, 0, 0, 0 }
};


static char* resource_find_file(char* filename);
static SDL_Surface* resource_load_png(char* filename);
char *strdup (const char *str);  // silly mingw

int resources_load(UI* ui)
{
	int i = 0;
	while(reslist[i].name)
	{
		// find file
		char* filepath = resource_find_file(reslist[i].filename);
		if(!filepath)
			errx(1, "Could not find file %s.", reslist[i].filename);

		// load image
		SDL_Surface* sf = NULL;
		if(endswith(reslist[i].filename, ".png"))
			sf = resource_load_png(filepath);
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
	return 1;
}


void resources_unload(UI* ui)
{
	struct SurfaceResource *res, *tmp;
	HASH_ITER(hh, resources, res, tmp)
	{
		if(res->sf)
			SDL_FreeSurface(res->sf);
		HASH_DEL(resources, res);
		free(res);
	}
}


SDL_Surface* res(const char* name)
{
	SurfaceResource *rs;
	HASH_FIND_STR(resources, name, rs);
	if(!rs)
		errx(1, "Could not find resource %s.", name);
	SDL_Surface* sf = rs->sf;
	free(rs);
	return sf;
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
		debug("Seeking %s...", buf[i]);
		struct stat b;
		if(stat(buf[i], &b) == 0)
			return strdup(buf[i]);
	}

	return NULL;
}


static SDL_Surface* resource_load_png(char* filename)
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
		err(1, "Error loading %s.\n");
	png_infop info_ptr = png_create_info_struct(png_ptr);

	/*
	// handle errors
	if(setjmp(png_ptr->jmpbuf))
	{
		png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
		errx(1, "something went wrong while reading %s", filename);
	}

	// read PNG file info
	int bitdepth, color_type;
	png_init_io(png_ptr, f);
	png_set_sig_bytes(png_ptr, 8);
	png_read_info(png_ptr, info_ptr);
	image[n].h = png_get_image_height(png_ptr, info_ptr);
	image[n].w = png_get_image_width(png_ptr, info_ptr);
	bitdepth = png_get_bit_depth(png_ptr, info_ptr);
	color_type = png_get_color_type(png_ptr, info_ptr);
	if(color_type != PNG_COLOR_TYPE_PALETTE || bitdepth != 8)
	{
		png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
		fprintf(stderr, "%s: only 8-bit paletted images are supported.\n",
			       	filename);
		return;
	}

	// copy colors
	image[n].palette = malloc(sizeof(png_color) * 256);
	memcpy(image[n].palette, p, sizeof(png_color) * 256);

	// get transparent color
	image[n].transparent = -1;
	if(png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS))
	{
		png_bytep trans_alpha;
		int num_trans;
		png_get_tRNS(png_ptr, info_ptr, &trans_alpha, &num_trans, NULL);
		if(num_trans > 0)
			image[n].transparent = trans_alpha[0];
	}

	// read image data
	image[n].row_pointers = malloc(sizeof(png_bytep) * image[n].h);
	int y;
	for(y=0; y<image[n].h; y++)
		image[n].row_pointers[y] = 
			malloc(png_get_rowbytes(png_ptr, info_ptr));
	png_read_image(png_ptr, image[n].row_pointers);

	// close
	if(png_ptr && info_ptr)
		png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
	fclose(f);
	*/
	
	return NULL;
}
