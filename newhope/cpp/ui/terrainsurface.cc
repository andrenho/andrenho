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
	st.push(res["water_c"]); // TODO

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
}
