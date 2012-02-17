#ifndef IMAGESET_H
#define IMAGESET_H

#include "SDL.h"

typedef struct
{
	char* filename;
	int n_images;
	SDL_Color color[256];
	char* color_name[256];
} Imageset;

typedef struct
{
	int w, h;
	SDL_Surface* sf;
	Imageset* imageset;
} Image;

Imageset* imageset_new(char* filename);
Image* imageset_add_image(Imageset* is);

#endif
