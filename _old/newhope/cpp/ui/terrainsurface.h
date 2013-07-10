#ifndef UI_TERRAINSURFACE_H
#define UI_TERRAINSURFACE_H

#include <map>
#include <queue>
#include <set>
#include <vector>

#include "util/point.h"
#include "util/rect.h"
#include "util/defines.h"
#include "world/world.h"

class GraphicLibrary;
class Image;
class Resources;
class World;

class TerrainSurface {
public:
	TerrainSurface(const World& world, const GraphicLibrary& video,
			const Resources& res) :
		Img(nullptr), world(world), video(video), res(res), 
		x(-10000), y(-10000), w(0), h(0) { }
	~TerrainSurface();

	void RedrawImg(std::vector<Rect>& rects);
	void Resize(int scr_w, int scr_h);
	void AreasToRedraw(std::vector<Rect>& rects);
	void SetTopLeft(Point<int> p);

	Image* Img;

private:
	void Redraw();
	void DrawTile(Point<int> p);
	const Image* TileSurface(Point<int> p);
	void BuildTile(Point<int> p, std::queue<const Image*>& st);
	void BuildTileBorders(Point<int> p, TerrainType t, 
			std::queue<const Image*>& st);
	void BuildBorder(TerrainType t, uint8_t bs, 
			std::queue<const Image*>& st);
	
	std::map<std::queue<const Image*>, const Image*> imagehash;

	const World& world;
	const GraphicLibrary& video;
	const Resources& res;
	int x, y, w, h;
	std::set<Point<int>> tiles_to_redraw;

	DISALLOW_COPY_AND_ASSIGN(TerrainSurface);
};

#endif
