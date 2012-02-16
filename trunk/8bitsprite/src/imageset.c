#include "imageset.h"

#include <stdlib.h>

Imageset* imageset_new(char* filename, int w, int h)
{
	Imageset* is = malloc(sizeof(Imageset));
	is->filename = filename;
	is->w = w;
	is->h = h;
	is->n_images = 0;
	return is;
}
