#ifndef UI_MINIMAP_H
#define UI_MINIMAP_H

#include <map>
#include <vector>

#include "libs/colors.h"
#include "util/point.h"
#include "util/defines.h"
#include "world/world.h"

class GraphicLibrary;
class Image;
class Resources;

class Minimap {
public:
	Minimap(GraphicLibrary const& video, World const& world, 
			Resources const& res);
	~Minimap();

	void Reset();
	void Display();

private:
	void Create();
	void SetupColors();
	void KillThread();
	void DrawPaper();
	void DrawMap();
	void DrawRivers();
	void DrawCities();
	void HandleEvents();
	void DrawPath(std::vector<Point<int>>& points, Color c);

	static int CreationThread(void* self);

	GraphicLibrary const& video;
	World const& world;
	Resources const& res;
	void* thread;
	Image* image;
	int sz;
	bool thread_killed;
	std::map<TerrainType, Color> colors;

	DISALLOW_COPY_AND_ASSIGN(Minimap);
};

#endif
