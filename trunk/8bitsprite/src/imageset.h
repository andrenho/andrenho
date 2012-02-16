#ifndef IMAGESET_H
#define IMAGESET_H

typedef struct
{
	char* filename;
	int w, h;
	int n_images;
} Imageset;

Imageset* imageset_new(char* filename, int w, int h);

#endif
