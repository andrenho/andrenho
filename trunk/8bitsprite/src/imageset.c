#include "imageset.h"

#include <stdlib.h>

Imageset* imageset_new(char* filename)
{
	Imageset* is = malloc(sizeof(Imageset));
	is->filename = filename;
	is->n_images = 0;
	return is;
}


Image* imageset_add_image(Imageset* is)
{
	Image* img = malloc(sizeof(Image));
	img->w = img->h = 32;
	img->sf = NULL; // TODO
	img->imageset = is;
	return img;
}
