#ifndef UI_TERRAINSURFACE_H
#define UI_TERRAINSURFACE_H

#include <vector>

#include "world/world.h"
#include "libs/rect.h"
#include "libs/image.h"

class TerrainSurface {
public:
	TerrainSurface(World const& world) :
		world(world) { }

	void Resize(int scr_w, int scr_h);
	void AreasToRedraw(std::vector<Rect>& rects);

	Image* Img;

	static const int TileSize = 32;
private:
	World const& world;
};

#endif
