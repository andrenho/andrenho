#ifndef IMAGESET_H
#define IMAGESET_H

#include "SDL.h"
#include "uthash/utarray.h"

struct Imageset;

typedef struct Image
{
	SDL_Surface* sf;
	struct Imageset* imageset;
	int _w, _h;
} Image;

typedef struct Imageset
{
	char* filename;
	SDL_Color color[256];
	char* color_name[256];
	UT_array *images;
} Imageset;

Imageset* imageset_new(char* filename);
Imageset* imageset_load(char* filename);
void imageset_save(Imageset* is);
Image* imageset_add_image(Imageset* is);
void imageset_delete_image(Imageset* is, int n);

static UT_icd image_icd = { sizeof(Image), NULL, NULL, NULL };

#endif
