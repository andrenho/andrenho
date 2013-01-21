#ifndef UI_TERRAINSURFACE_H
#define UI_TERRAINSURFACE_H

#include <cstdint>
#include <cstdlib>
#include <climits>
#include <map>
#include <queue>
#include <set>
#include <vector>

#include "libs/graphiclibrary.h"
#include "util/point.h"
#include "util/rect.h"
#include "libs/image.h"
#include "ui/resource.h"
#include "world/world.h"

class TerrainSurface {
public:
	TerrainSurface(World const& world, GraphicLibrary const& video,
			Resources const& res) :
		Img(NULL), world(world), video(video), res(res), 
		x(-10000), y(-10000), w(0), h(0) { }
	~TerrainSurface();

	void RedrawImg(std::vector<Rect>& rects);
	void Resize(int scr_w, int scr_h);
	void AreasToRedraw(std::vector<Rect>& rects);
	void SetTopLeft(Point<int> p);

	Image* Img;

	static const int TileSize = 32;

private:
	void Redraw();
	void DrawTile(Point<int> p);
	const Image* TileSurface(Point<int> p);
	void BuildTile(Point<int> p, std::queue<Image const*>& st);
	void BuildTileBorders(Point<int> p, TerrainType t, 
			std::queue<Image const*>& st);
	void BuildBorder(TerrainType t, uint8_t bs, 
			std::queue<Image const*>& st);
	
	std::map<std::queue<Image const*>, Image const*> imagehash;

	World const& world;
	GraphicLibrary const& video;
	Resources const& res;
	int x, y, w, h;
	std::set<Point<int>> tiles_to_redraw;
};

#endif
