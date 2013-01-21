#include "ui/terrainsurface.h"

#include <algorithm>
#include <bitset>
#include <sstream>
#include <vector>

#include "libs/image.h"
#include "util/logger.h"
#include "world/world.h"

TerrainSurface::~TerrainSurface()
{
	for(auto const& image: imagehash)
		delete image.second;
	if(Img)
		delete Img;
}


void
TerrainSurface::RedrawImg(std::vector<Rect>& rects)
{
	for(auto const& tile: tiles_to_redraw)
	{
		rects.push_back(Rect(tile.x, tile.y, TileSize, TileSize));
		DrawTile(tile);
	}
	tiles_to_redraw.clear();
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

	tiles_to_redraw.clear();
	Redraw();

	logger.Debug("window resize resquested: %d %d", w, h);
	logger.Debug("trsurf resize: %d %d (%d %d)", Img->w, Img->h, w, h);
}


void 
TerrainSurface::AreasToRedraw(std::vector<Rect>& rects)
{
}


void 
TerrainSurface::SetTopLeft(Point<int> p)
{
	tiles_to_redraw.clear();

	if(this->x == p.x && this->y == p.y)
		return;

	if(abs(this->x - p.x)*TileSize > video.Window->w
	|| abs(this->y - p.y)*TileSize > video.Window->h)
	{
		this->x = p.x;
		this->y = p.y;
		Redraw();
	}
	else
	{
		int nx, ny;

		Rect r((this->x - p.x)*TileSize, (this->y - p.y)*TileSize);
		Img->Blit(*Img, r);

		int tsx = this->x, 
		    tsy = this->y;

		this->x = p.x;
		this->y = p.y;

		if(p.x > tsx)
			for(nx=(this->w + this->x - (p.x - tsx)); nx < (this->w + this->x); nx++)
				for(ny=this->y; ny < (this->h + this->y); ny++)
					tiles_to_redraw.insert(Point<int>(nx, ny));
		else if(p.x < tsx)
			for(nx=this->x; nx < (this->x + tsx - p.x); nx++)
				for(ny=this->y; ny < (this->h + this->y); ny++)
					tiles_to_redraw.insert(Point<int>(nx, ny));
		if(p.y > tsy)
			for(ny=(this->h + this->y - (p.y - tsy)); ny < (this->h + this->y); ny++)
				for(nx=this->x; nx < (this->w + this->x); nx++)
					tiles_to_redraw.insert(Point<int>(nx, ny));
		else if(p.y < tsy)
			for(ny=this->y; ny < (this->y + tsy - p.y); ny++)
				for(nx=this->x; nx < (this->w + this->x); nx++)
					tiles_to_redraw.insert(Point<int>(nx, ny));
	}
}


void
TerrainSurface::Redraw()
{
	for(int x=this->x; x<(this->x + this->w); x++)
		for(int y=this->y; y<(this->y + this->h); y++)
			tiles_to_redraw.insert(Point<int>(x, y));
}


void 
TerrainSurface::DrawTile(Point<int> p)
{
	Rect r((p.x - this->x) * TileSize, 
	       (p.y - this->y) * TileSize, 
	       TileSize, TileSize);

	const Image* img = TileSurface(p);
	img->Blit(*Img, r);
}


const Image* 
TerrainSurface::TileSurface(Point<int> p)
{
	// build queue
	std::queue<Image const*> st;
	BuildTile(p, st);

	// lookup in the hash
	if(imagehash.find(st) == imagehash.end())
	{
		// not found, create image
		Image* image = video.CreateImage(TileSize, TileSize);
		imagehash[st] = image;
		while(!st.empty())
		{
			st.front()->Blit(*image);
			st.pop();
		}
		return image;
	}
	return imagehash[st];
}


static std::map<TerrainType, std::string> basic {
	{ t_GRASS,    "grass"    },
	{ t_WATER,    "water"    },
	{ t_DIRT,     "dirt"     },
	{ t_EARTH,    "earth"    },
	{ t_LAVAROCK, "lavarock" },
	{ t_LAVA,     "lava"     },
	{ t_SNOW,     "snow"     },

	/* TODO */
	{ t_HOTFOREST, "grass" },
	{ t_TUNDRA, "earth" },
	{ t_COLDFOREST, "grass" },
};


void 
TerrainSurface::BuildTile(Point<int> p, std::queue<Image const*>& st)
{
	// basic terrain
	TerrainType terrain = world.Terrain(p);
	std::string basic_terrain = basic[terrain];
	int special;
	if((special = world.Special(p)) == 0)
		st.push(res[basic_terrain + "_c"]);
	else
	{
		std::stringstream s;
		s << basic_terrain << "_" << special;
		st.push(res[s.str()]);
	}

	BuildTileBorders(p, terrain, st);
}


void
TerrainSurface::BuildTileBorders(Point<int> p, TerrainType t, 
		std::queue<Image const*>& st)
{
	// find terrains around
	TerrainType around[8] = {
		world.Terrain(Point<int>(p.x-1, p.y-1)),
		world.Terrain(Point<int>(p.x  , p.y-1)),
		world.Terrain(Point<int>(p.x+1, p.y-1)),
		world.Terrain(Point<int>(p.x-1, p.y  )),
		world.Terrain(Point<int>(p.x+1, p.y  )),
		world.Terrain(Point<int>(p.x-1, p.y+1)),
		world.Terrain(Point<int>(p.x  , p.y+1)),
		world.Terrain(Point<int>(p.x+1, p.y+1))
	};
	
	// compact list and order by importance
	std::vector<TerrainType> terrains;
	for(int i=0; i<8; i++)
	{
		if(std::find(terrains.begin(), terrains.end(), around[i]) ==
				terrains.end())
			terrains.push_back(around[i]);
	}
	std::sort(terrains.begin(), terrains.end());

	// find borders
	for(auto const& terrain: terrains)
	{
		if(terrain <= t)
			continue;
		uint8_t bs = 0;
		for(int i=0; i<8; i++)
			bs |= ((around[i] == terrain) << i);
		BuildBorder(terrain, bs, st);
	}
}


void
TerrainSurface::BuildBorder(TerrainType t, uint8_t bs, 
		std::queue<Image const*>& st)
{
	struct { int nw, n, ne, w, e, sw, s, se; } b = {
		(bs & 0b00000001), (bs & 0b00000010), (bs & 0b00000100),
		(bs & 0b00001000), 		      (bs & 0b00010000),
 		(bs & 0b00100000), (bs & 0b01000000), (bs & 0b10000000) };

	// find the most t tile around this one
	if(b.s && b.w)
		st.push(res[basic[t] + "_ic_sw"]);
	else if(b.s && b.e)
		st.push(res[basic[t] + "_ic_se"]);
	else if(b.n && b.w)
		st.push(res[basic[t] + "_ic_nw"]);
	else if(b.n && b.e)
		st.push(res[basic[t] + "_ic_ne"]);
	else if(b.n || b.s || b.w || b.e)
	{
		if(b.n)
			st.push(res[basic[t] + "_ec_s"]);
		if(b.s)
			st.push(res[basic[t] + "_ec_n"]);
		if(b.e)
			st.push(res[basic[t] + "_ec_w"]);
		if(b.w)
			st.push(res[basic[t] + "_ec_e"]);
	}
	else if(b.se || b.sw)
	{
		if(b.se)
			st.push(res[basic[t] + "_ec_nw"]);
		if(b.sw)
			st.push(res[basic[t] + "_ec_ne"]);
	}
	else if(b.ne || b.nw)
	{
		if(b.ne)
			st.push(res[basic[t] + "_ec_sw"]);
		if(b.nw)
			st.push(res[basic[t] + "_ec_se"]);
	}
}
