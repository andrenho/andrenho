#include "resource.h"

#include <stdlib.h>
#include "SDL.h"
#include "SDL_image.h"

#include "ui/ui.h"
#include "util/log.h"
#include "util/strings.h"
#include "util/uthash.h"

typedef struct SurfaceResource {
	char name[20];
	SDL_Surface* sf;
	struct UT_hash_handle hh;
} SurfaceResource;
static SurfaceResource* resources = NULL;

static struct { 
	char *name, *filename;
	int x, y, w, h;
} reslist[] = {
	{ "grassm", "grass.png", 96, 32, 32, 32 },
	{ NULL, NULL, 0, 0, 0, 0 }
};


static SDL_Surface* resource_load_png(char* filename);


int resources_load(UI* ui)
{
	int i = 0;
	while(reslist[i].name)
	{
		// load image
		SDL_Surface* sf = NULL;
		if(endswith(reslist[i].filename, ".png"))
			sf = resource_load_png(reslist[i].filename);
		else
		{
			errx(1, "Invalid file type %s.", reslist[i].filename);
			return 0;
		}

		// verify
		if(!sf)
		{
			errx(1, "Error loading resource %s.", reslist[i].filename);
			return 0;
		}

		// add to hash
		SurfaceResource* res = malloc(sizeof(SurfaceResource));
		strncpy(res->name, reslist[i].name, 20);
		res->name[19] = 0;
		res->sf = sf;
		HASH_ADD_STR(resources, name, res);

		++i;
	}
	return 1;
}


void resources_unload(UI* ui)
{
	struct SurfaceResource *res, *tmp;
	HASH_ITER(hh, resources, res, tmp)
	{
		if(res->sf)
			SDL_FreeSurface(res->sf);
		HASH_DEL(resources, res);
		free(res);
	}
}


/*
 * STATIC
 */


static SDL_Surface* resource_load_png(char* filename)
{
	char buf[1024];
	snprintf(buf, 1023, DATADIR "/%s", filename);
	SDL_Surface* sf = IMG_Load(buf);
	if(!sf)
	{
		warnx("Could not load %s: %s.", filename, IMG_GetError());
		snprintf(buf, 1023, "data/%s", filename);
		sf = IMG_Load(buf);
		if(!sf)
			warnx("Could not load %s: %s.", filename, IMG_GetError());
	}
	return sf;
}
