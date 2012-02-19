#include "imageset.h"

#include <stdlib.h>

#include <archive.h>
#include <archive_entry.h>
#include <confuse.h>
#include <tar.h>

#include "util.h"

static UT_icd image_icd = { sizeof(Image), NULL, NULL, NULL };

static void create_config_file(Imageset* is, struct archive* a);
static void write_image_files(Imageset* is, struct archive* a);


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


Imageset* imageset_load(char* filename)
{
	// initialize imageset
	Imageset* is = malloc(sizeof(Imageset));
	is->filename = filename;
	utarray_new(is->images, &image_icd);

	// open archive
	
	// read config contents
	
	// read image file
	
	// close archive
	
	return is;
}


void imageset_save(Imageset* is)
{
	struct archive *a;

	// create compressed file
	a = archive_write_new();
	archive_write_set_compression_gzip(a);
	archive_write_set_format_pax_restricted(a);
	archive_write_open_filename(a, is->filename);

	// write configuration file
	create_config_file(is, a);
	
	// write image files
	write_image_files(is, a);
	
	// close file
	archive_write_finish(a);
}


Image* imageset_add_image(Imageset* is)
{
	Image* img = malloc(sizeof(Image));
	img->imageset = is;

	img->sf = SDL_CreateRGBSurface(SDL_SWSURFACE, 32, 32, 8, 0, 0, 0, 0);
	SDL_SetColors(img->sf, is->color, 0, 256);
	SDL_SetColorKey(img->sf, SDL_SRCCOLORKEY|SDL_RLEACCEL, 255);
	SDL_FillRect(img->sf, NULL, TRANSPARENT);
	
	P(img->sf, 0, 0) = 254;
	P(img->sf, 10, 10) = 254;
	P(img->sf, 31, 31) = 254;

	utarray_push_back(is->images, img);
	
	return img;
}


void imageset_delete_image(Imageset* imageset, int n)
{
	Image* img = (Image*)utarray_eltptr(imageset->images, n);
	if(!img)
		abort();
	SDL_FreeSurface(img->sf);
	utarray_erase(imageset->images, n, 1);
}


static void create_config_file(Imageset* is, struct archive *a)
{
	struct archive_entry *entry;

	// create file in the archive
	entry = archive_entry_new();
	archive_entry_set_pathname(entry, "config.txt");
	archive_entry_set_filetype(entry, AE_IFREG);
	archive_entry_set_perm(entry, 0644);

	// write config file in the memory
	char* bp;
	size_t size;
	FILE* f = open_memstream(&bp, &size);

	// header
	fprintf(f, "version=0.1\n\n");

	// colormaps
	fprintf(f, "colormap {\n");
	int i;
	for(i=0; i<256; i++)
	{
		fprintf(f, "\tcolor {\n");
		if(strlen(is->color_name[i]) > 0)
			fprintf(f, "\t\tname = %s\n", is->color_name[i]);
		fprintf(f, "\t\tcolors = { %d, %d, %d }\n",
				is->color[i].r, is->color[i].g, is->color[i].b);
		fprintf(f, "\t}\n");
	}
	fprintf(f, "}\n");

	
	// images
	size_t offset = 0x0;
	for(i=0; i<utarray_len(is->images); i++)
	{
		Image* img = (Image*)utarray_eltptr(is->images, i);
		fprintf(f, "image {\n");
		fprintf(f, "\tw = %d\n", img->sf->w);
		fprintf(f, "\th = %d\n", img->sf->h);
		fprintf(f, "\toffset = %ld\n", offset);
		fprintf(f, "}\n\n");
		offset += (img->sf->w * img->sf->h);
	}

	fclose(f);

	// store in the archive
	archive_entry_set_size(entry, size);
	archive_write_header(a, entry);
	archive_write_data(a, bp, size);
	archive_entry_free(entry);
}


static void write_image_files(Imageset* is, struct archive* a)
{
	struct archive_entry *entry;

	// create file in the archive
	entry = archive_entry_new();
	archive_entry_set_pathname(entry, "images.dat");
	archive_entry_set_filetype(entry, AE_IFREG);
	archive_entry_set_perm(entry, 0644);

	// write images file in the memory
	char* bp;
	size_t size;
	FILE* f = open_memstream(&bp, &size);
	int i;
	for(i=0; i<utarray_len(is->images); i++)
	{
		Image* img = (Image*)utarray_eltptr(is->images, i);
		fwrite(img->sf->pixels, 1, (img->sf->w * img->sf->h), f);
	}
	fclose(f);

	// store in the archive
	archive_entry_set_size(entry, size);
	archive_write_header(a, entry);
	archive_write_data(a, bp, size);
	archive_entry_free(entry);
}
