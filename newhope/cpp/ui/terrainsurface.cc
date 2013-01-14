#include "ui/terrainsurface.h"

#include <sstream>

#include "libs/image.h"
#include "util/logger.h"
#include "world/world.h"

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
	int nx, ny;

	if(this->x == x && this->y == y)
		return;

	Rect r((this->x - x)*TileSize, (this->y - y)*TileSize);
	Img->Blit(*Img, r);

	int tsx = this->x, 
	    tsy = this->y;

	this->x = x;
	this->y = y;

	if(x > tsx)
		for(nx=(this->w + this->x - (x - tsx)); nx < (this->w + this->x); nx++)
			for(ny=this->y; ny < (this->h + this->y); ny++)
				DrawTile(nx, ny);
	else if(x < tsx)
		for(nx=this->x; nx < (this->x + tsx - x); nx++)
			for(ny=this->y; ny < (this->h + this->y); ny++)
				DrawTile(nx, ny);
	if(y > tsy)
		for(ny=(this->h + this->y - (y - tsy)); ny < (this->h + this->y); ny++)
			for(nx=this->x; nx < (this->w + this->x); nx++)
				DrawTile(nx, ny);
	else if(y < tsy)
		for(ny=this->y; ny < (this->y + tsy - y); ny++)
			for(nx=this->x; nx < (this->w + this->x); nx++)
				DrawTile(nx, ny);
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
	BuildTile(x, y, st);

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


void 
TerrainSurface::BuildTile(int x, int y, std::stack<Image const*>& st)
{
	static std::map<TerrainType, std::string> basic {
		{ t_GRASS,    "grass"    },
		{ t_WATER,    "water"    },
		{ t_DIRT,     "dirt"     },
		{ t_EARTH,    "earth"    },
		{ t_LAVAROCK, "lavarock" },
		{ t_LAVA,     "lava"     },
		{ t_SNOW,     "snow"     },
	};

	// basic terrain
	std::string basic_terrain = basic[world.Terrain(x, y)];
	int special;
	if((special = world.Special(x, y)) == 0)
		st.push(res[basic_terrain + "_c"]);
	else
	{
		std::stringstream s;
		s << basic_terrain << "_" << special;
		st.push(res[s.str()]);
	}
}
