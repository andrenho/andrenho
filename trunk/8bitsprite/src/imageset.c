#include "imageset.h"

#include <stdlib.h>

#include "util.h"

Imageset* imageset_new(char* filename)
{
	Imageset* is = malloc(sizeof(Imageset));
	is->filename = filename;
	is->n_images = 0;
	int i;
	for(i=0;i<254;i++)
		is->color[i].r = is->color[i].g = is->color[i].b = 0;
	is->color[254].r = is->color[254].g = is->color[254].b = 255;
	is->color[255].r = is->color[255].g = is->color[255].b = 128;
	return is;
}


Image* imageset_add_image(Imageset* is)
{
	Image* img = malloc(sizeof(Image));
	img->w = img->h = 32;
	img->sf = SDL_CreateRGBSurface(SDL_SWSURFACE, 32, 32, 8, 0, 0, 0, 0);
	img->imageset = is;
	printf("%d\n", is->color[254].r);
	SDL_SetColors(img->sf, is->color, 0, 256);

	SDL_Rect r = { 0, 0, 32, 32 };
	SDL_FillRect(img->sf, NULL, 0);
	P(img->sf, 10, 10) = 254;
	return img;
}
