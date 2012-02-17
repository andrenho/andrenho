#include "imageset.h"

#include <stdlib.h>

#include "util.h"

static UT_icd image_icd = { sizeof(Image), NULL, NULL, NULL };

Imageset* imageset_new(char* filename)
{
	Imageset* is = malloc(sizeof(Imageset));
	is->filename = filename;
	utarray_new(is->images, &image_icd);

	// colors
	int i;
	for(i=0;i<254;i++)
		is->color[i].r = is->color[i].g = is->color[i].b = 0;
	is->color[254].r = is->color[254].g = is->color[254].b = 255;
	is->color[255].r = is->color[255].g = is->color[255].b = 128;

	for(i=0;i<255;i++)
		is->color_name[i] = "";
	is->color_name[0] = "Black";
	is->color_name[254] = "White";
	is->color_name[255] = "Transparent";

	return is;
}


Image* imageset_add_image(Imageset* is)
{
	Image* img = malloc(sizeof(Image));
	img->imageset = is;

	img->sf = SDL_CreateRGBSurface(SDL_SWSURFACE, 32, 32, 8, 0, 0, 0, 0);
	SDL_SetColors(img->sf, is->color, 0, 256);
	SDL_SetColorKey(img->sf, SDL_SRCCOLORKEY|SDL_RLEACCEL, 255);
	SDL_Rect r = { 0, 0, 32, 32 };
	SDL_FillRect(img->sf, NULL, TRANSPARENT);
	
	P(img->sf, 0, 0) = 254;
	P(img->sf, 10, 10) = 254;
	P(img->sf, 31, 31) = 254;

	utarray_push_back(is->images, img);
	
	return img;
}
