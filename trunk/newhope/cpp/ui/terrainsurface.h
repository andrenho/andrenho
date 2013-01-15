#ifndef UI_TERRAINSURFACE_H
#define UI_TERRAINSURFACE_H

#include <cstdint>
#include <cstdlib>
#include <map>
#include <queue>
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
	void BuildTile(int x, int y, std::queue<Image const*>& st);
	void BuildTileBorders(int x, int y, TerrainType t, 
			std::queue<Image const*>& st);
	void BuildBorder(TerrainType t, uint8_t bs, 
			std::queue<Image const*>& st);
	
	std::map<std::queue<Image const*>, Image const*> imagehash;

	World const& world;
	GraphicLibrary const& video;
	Resources const& res;
	int x, y, w, h;
};

#endif
