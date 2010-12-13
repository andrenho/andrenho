#include "tilegame.h"

#include <archive.h>
#include <stdlib.h>

// 
// private
//
static int 
load_index(TileGame* tg)
{
	struct archive_entry *entry;

	int r = archive_read_open_filename(tg->_a, tg->_filename, 10240);
	if(r != ARCHIVE_OK)
	{
		tg->error = "Error opening archive.";
		return 0;
	}

	while(archive_read_next_header(tg->_a, &entry) == ARCHIVE_OK)
		printf("%s\n",archive_entry_pathname(entry));
	
	return -1;
}


static int 
load_layer(TileGame* tg, int idx)
{
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

	// initialize libarchive
	tg->_a = archive_read_new();
	archive_read_support_compression_all(tg->_a);
	archive_read_support_format_all(tg->_a);

	// get index and create layers
	tg->_filename = filename;
	if(!load_index(tg))
		goto _error;
	
	// load tiles
	int i;
	for(i=0; i<tg->layers; i++)
		if(!load_layer(tg, i))
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
	archive_read_finish(tg->_a);
	SDL_Quit();
}
