#include "ui/terrainsurface.h"

#include "libs/image.h"
#include "util/logger.h"

TerrainSurface::~TerrainSurface()
{
	if(Img)
		delete Img;
}


void 
TerrainSurface::Resize(int scr_w, int scr_h)
{
	if(Img)
		delete Img;
	Img = video.CreateImage(scr_w + (TileSize + (scr_w % TileSize)),
			        scr_h + (TileSize + (scr_h % TileSize)));
	w = Img->w / TileSize;
	h = Img->h / TileSize;
	Redraw();

	logger.Debug("window resize resquested: %d %d", w, h);
	logger.Debug("trsurf resize: %d %d (%d %d)", Img->w, Img->h, w, h);
}


void 
TerrainSurface::AreasToRedraw(std::vector<Rect>& rects)
{
}


void 
TerrainSurface::SetTopLeft(int x, int y)
{
}


void
TerrainSurface::Redraw()
{
	for(int x=this->x; x<(this->x + this->w); x++)
		for(int y=this->y; y<(this->y + this->h); y++)
			DrawTile(x, y);
}


void 
TerrainSurface::DrawTile(int x, int y)
{
	Rect r((x - this->x) * TileSize, 
	       (y - this->y) * TileSize, 
	       TileSize, TileSize);
	TileSurface(x, y)->Blit(*Img, r);
}


const Image* 
TerrainSurface::TileSurface(int x, int y)
{
	// build stack
	std::stack<Image const*> st;
	st.push(res["water"]); // TODO

	// lookup in the hash
	if(imagehash.find(st) == imagehash.end())
	{
		// not found, create image
		Image* image = video.CreateImage(TileSize, TileSize);
		imagehash[st] = image;
		while(!st.empty())
		{
			st.top()->Blit(*image);
			st.pop();
		}
		return image;
	}
	return imagehash[st];

	/*
	SDL_Surface *sf;
	
	// build stack
	SDL_Surface* stack[MAX_STACK] = { [0 ... (MAX_STACK-1)] = NULL };
	build_tile(ts->world, x, y, stack);

	// find hash key
	char id[RES_CHARS * 12] = { [0 ... (MAX_STACK* 12-1)] = 0 };
	stack_to_char(stack, id);

	// find image in hash
	SurfaceHash* sh;
	HASH_FIND_STR(sfhash, id, sh);
	if(!sh) // image not found, build it
	{
		// create image
		int i = 0;
		SDL_Surface* _sf = SDL_CreateRGBSurface(SDL_SWSURFACE,
				TILESIZE, TILESIZE, 32, 
				0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000);
		sf = SDL_DisplayFormat(_sf);
		SDL_FreeSurface(_sf);
		SDL_FillRect(sf, NULL, 0);
		while(stack[i])
		{
			SDL_BlitSurface(stack[i], NULL, sf, NULL);
			i++;
		}

		// add to hash
		sh = malloc(sizeof(SurfaceHash));
		strcpy(sh->id, id);
		sh->sf = sf;
		HASH_ADD_STR(sfhash, id, sh);
	}
	else
		sf = sh->sf;

	assert(sf);
	return sf;
	*/
	return res["water"];
}
