#include "tilegame.h"

#include <archive.h>
#include <archive_entry.h>
#include <stdlib.h>


// 
// private
//
static char*
read_from_archive(TileGame* tg, const char* archive, const char* file, 
		int64_t* sz)
{
	struct archive* a;
	struct archive_entry *entry;
	char* data = NULL;

	// open archive
	a = archive_read_new();
	archive_read_support_compression_all(a);
	archive_read_support_format_all(a);
	int r = archive_read_open_filename(a, archive, 10240);
	if(r != ARCHIVE_OK)
	{
		tg->error = "Error opening archive.";
		return NULL;
	}

	// search for file
	int found = 0;
	while(archive_read_next_header(a, &entry) == ARCHIVE_OK)
	{
		if(!strcmp(archive_entry_pathname(entry), file))
		{
			found = 1;

			// load file
			*sz = archive_entry_size(entry);
			data = malloc((*sz)+1);
			archive_read_data_into_buffer(a, data, *sz);
			data[*sz] = '\0';
			goto end;
		}
	}
	if(!found)
	{
		tg->error = "index.rc not found in archive.";
		data = NULL;
	}

end:
	// close archive
	r = archive_read_finish(a);
	if(r != ARCHIVE_OK)
	{
		tg->error = "Error closing archive.";
		data = NULL;
	}
	return data;
}


static Layer*
load_layer(TileGame* tg, int n_layer, const char* archive, const char* filename)
{
	// read from archive
	int64_t sz;
	char* data = read_from_archive(tg, archive, filename, &sz);
	if(!data)
		return NULL;

	// create layer
	Layer* layer = malloc(sizeof(Layer));

	// read index.rc
	int64_t i = -1;
	while(i < (sz-2))
	{
		char cmd[25];
		int c, n;
		c = sscanf(&data[i], "%24s%n", cmd, &n);
		i += n;

		if(c != 1)
		{
			tg->error = "Invalid command.";
			return 0;
		}

		if(!strcmp(cmd, "image"))
		{
			c = sscanf(&data[i], "\"%254[^\"]\" %d %d%n", 
					layer->image_file,
					&layer->tile_w, &layer->tile_h, &n);
//			if(c != 4
		}
		else if(!strcmp(cmd, "tile"))
		{
		}
		else
		{
			tg->error = "Invalid command";
			return NULL;
		}
	}

	free(data);
	return layer;
}


static int 
load_index(TileGame* tg, const char* archive)
{
	int64_t sz;
	char* data = read_from_archive(tg, archive, "index.rc", &sz);
	if(!data)
		return 0;

	// read index.rc
	int64_t i = -1;
	while(i < (sz-2))
	{
		char cmd[25], filename[255];
		int layer, n, c;
		c = sscanf(data, "%24s %d \"%254[^\"]\"%n", 
				cmd, &layer, filename, &n);
		i += n;
		
		if(c == 3 && !strcmp(cmd, "layer"))
		{
			Layer* ly = load_layer(tg, layer, archive, filename);
			if(!ly)
				return 0;
			HASH_ADD_INT(tg->layers, id, ly);
		}
		else
		{
			tg->error = "Invalid index.rc file.";
			return 0;
		}
	}

	free(data);
	return -1;
}



static void 
sdl_error(const char* fct, TileGame* tg)
{
	tg->error = malloc(1024);
	sprintf(tg->error, "Error calling '%s': %s\n", fct, SDL_GetError());
}


// 
// public
//
TileGame* 
TG_Init(const char* filename, char** error)
{
	// create structure
	TileGame* tg = malloc(sizeof(TileGame));
	memset(tg, sizeof(TileGame), 0);

	// initialize SDL
	if(SDL_Init(SDL_INIT_VIDEO))
	{
		sdl_error("SDL_Init", tg);
		goto _error;
	}

	// read index and create layers
	if(!load_index(tg, filename))
		goto _error;
	
	return tg;

_error:
	if(error)
		*error = strdup(tg->error);
	free(tg);
	return NULL;
}


void 
TG_Quit(TileGame* tg)
{
	SDL_Quit();
}
