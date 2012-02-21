#include "imageset.h"

#include <stdio.h>
#include <stdlib.h>

#include <archive.h>
#include <archive_entry.h>
#include <tar.h>

static void read_config_file(Imageset* is, struct archive* a);
static char* read_image_file(struct archive* a, struct archive_entry* entry);
static void create_config_file(Imageset* is, struct archive* a);
static void write_image_files(Imageset* is, struct archive* a);


Imageset* imageset_load(char* filename)
{
	// initialize imageset
	Imageset* is = malloc(sizeof(Imageset));
	is->filename = filename;
	utarray_new(is->images, &image_icd);

	// open archive
	struct archive_entry *entry;
	struct archive *a = archive_read_new();
	archive_read_support_compression_gzip(a);
	archive_read_support_format_tar(a);

	// load images temporarily
	void* images[20480]; // TODO

	// open archive and read config
	if(archive_read_open_filename(a, filename, 16384) != ARCHIVE_OK)
	{
		fprintf(stderr, "%s is a invalid or non-existent file.\n",
				filename);
		exit(1);
	}
	while(archive_read_next_header(a, &entry) == ARCHIVE_OK)
	{
		const char* filename = archive_entry_pathname(entry);
		if(strcmp(filename, "config.txt") == 0)
			// read config
			read_config_file(is, a);
		else
		{
			// create image and read from archive
			char* endptr = (char*)&filename[5];
			int v = strtol(filename, &endptr, 10);
			void* img = read_image_file(a, entry);
			images[v] = img;
		}
	}
	
	// close archive
	archive_read_finish(a);

	// import images
	/* (the images are stored in a temporary array first because it might
	    happend that the images are found before the config.txt in the
	    archive) */
	int i;
	for(i=0; i<utarray_len(is->images); i++)
	{
		Image* img = (Image*)utarray_eltptr(is->images, i);
		img->sf = SDL_CreateRGBSurfaceFrom(images[i], img->_w, img->_h,
				8, img->_w, 0, 0, 0, 0);
		printf("%x\n", img->sf[500]);
		SDL_SetColors(img->sf, is->color, 0, 256);
		SDL_SetColorKey(img->sf, SDL_SRCCOLORKEY|SDL_RLEACCEL, 255);
	}
	
	return is;
}


static void invalid_file(Imageset* is)
{
	fprintf(stderr, "Invalid file %s.\n", is->filename);
	exit(1);
}


static void read_config_file(Imageset* is, struct archive* a)
{
	char buffer[20480];
	archive_read_data(a, buffer, 20480);

	int c = 0;
	char w[15];
	sscanf(&buffer[c], "%15s%n", &w, &c);
	if(strcmp(w, "#") == 0)
	{
		for(;;)
		{
			int n;
			char x[15];
			sscanf(&buffer[c], "%15s%n", &x, &n); c += n;
			if(strcmp(x, "colormap") == 0)
			{
				do {
					// read color information
					int i, r, g, b;
					char name[256];
					sscanf(&buffer[c], 
						"%d %d %d %d %256s\n%n", 
						&i, &r, &g, &b, &name, &n);
					c += n;
					is->color[i].r = r;
					is->color[i].g = g;
					is->color[i].b = b;
					is->color_name[i] = strdup(name);

					sscanf(&buffer[c], "%15s%n", &w, &n);
				} while(strcmp(w, "#") != 0);
				c += n;
			}
			else if(strcmp(x, "images") == 0)
			{
				do {
					// create new image
					Image* img = malloc(sizeof(Image));
					img->imageset = is;
					char filename[255], name[255];

					// read info from file
					sscanf(&buffer[c], 
						"%d %d %255s %255s\n%n",
						&img->_w, &img->_h, filename,
						name, &n); c += n;
				
					// insert into array
					char* endptr = (char*)&filename[5];
					int v = strtol(filename, &endptr, 10);
					if(v+1 >= utarray_len(is->images))
						utarray_resize(is->images, v);
					utarray_insert(is->images, img, v);

					sscanf(&buffer[c], "%15s%n", &w, &n);
				} while(strcmp(w, "#") != 0);
				c += n;
			}
			else if(strcmp(x, "end") == 0)
				break;
			else
				invalid_file(is);
		}
	}
	else
		invalid_file(is);
}


static char* read_image_file(struct archive* a, struct archive_entry* entry)
{
	size_t size = archive_entry_size(entry);
	char* pixels = malloc(size);
	archive_read_data(a, pixels, size);
	return pixels;
}


/*****************************************************************/


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

	// colormaps
	fprintf(f, "# colormap\n");
	int i;
	for(i=0; i<256; i++)
		fprintf(f, "%d %d %d %d %s\n", i,
				is->color[i].r, is->color[i].g, is->color[i].b,
				strlen(is->color_name[i]) ? is->color_name[i] : 
						"untitled");
	
	// images
	fprintf(f, "# images\n");
	for(i=0; i<utarray_len(is->images); i++)
	{
		Image* img = (Image*)utarray_eltptr(is->images, i);
		fprintf(f, "%d %d %04d.dat %s\n", img->sf->w, img->sf->h, i,
				"untitled");
	}

	fprintf(f, "# end");
	fclose(f);

	// store in the archive
	archive_entry_set_size(entry, size);
	archive_write_header(a, entry);
	archive_write_data(a, bp, size);
	archive_entry_free(entry);
	free(bp);
}


static void write_image_files(Imageset* is, struct archive* a)
{
	struct archive_entry *entry;

	int i;
	for(i=0; i<utarray_len(is->images); i++)
	{
		char filename[50];
		sprintf(filename, "%04d.dat", i);

		// create file in the archive
		entry = archive_entry_new();
		archive_entry_set_pathname(entry, filename);
		archive_entry_set_filetype(entry, AE_IFREG);
		archive_entry_set_perm(entry, 0644);

		// write images file in the memory
		char* bp;
		size_t size;
		FILE* f = open_memstream(&bp, &size);
		Image* img = (Image*)utarray_eltptr(is->images, i);
		fwrite(img->sf->pixels, 1, (img->sf->w * img->sf->h), f);
		fclose(f);

		// store in the archive
		archive_entry_set_size(entry, size);
		archive_write_header(a, entry);
		archive_write_data(a, bp, size);
		archive_entry_free(entry);
		free(bp);
	}
}

