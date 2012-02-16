#ifndef IMAGESET_H
#define IMAGESET_H

#include "SDL.h"

typedef struct
{
	char* filename;
	int n_images;
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
