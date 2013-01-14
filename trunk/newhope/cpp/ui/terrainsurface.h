#ifndef UI_TERRAINSURFACE_H
#define UI_TERRAINSURFACE_H

#include <cstdlib>
#include <map>
#include <stack>
#include <vector>

#include "libs/graphiclibrary.h"
#include "libs/rect.h"
#include "libs/image.h"
#include "ui/resource.h"
#include "world/world.h"

class TerrainSurface {
public:
	TerrainSurface(World const& world, GraphicLibrary const& video,
			Resources const& res) :
		Img(NULL), world(world), video(video), res(res), 
		x(0), y(0), w(0), h(0) { }
	~TerrainSurface();

	void Resize(int scr_w, int scr_h);
	void AreasToRedraw(std::vector<Rect>& rects);
	void SetTopLeft(int x, int y);

	Image* Img;

	static const int TileSize = 32;
private:
	void Redraw();
	void DrawTile(int x, int y);
	const Image* TileSurface(int x, int y);
	std::map<std::stack<Image const*>, Image const*> imagehash;

	World const& world;
	GraphicLibrary const& video;
	Resources const& res;
	int x, y, w, h;
};

#endif
