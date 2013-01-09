#ifndef UI_MINIMAP_H
#define UI_MINIMAP_H

#include <map>

#include "libs/graphiclibrary.h"
#include "libs/colors.h"
#include "ui/resource.h"
#include "world/world.h"

class Minimap {
public:
	Minimap(GraphicLibrary& video, World const& world, Resources const& res);
	~Minimap();

	void Reset();
	void Display();

private:
	void SetupColors();
	void KillThread();
	void DrawPaper();
	void DrawMap();
	void DrawRivers();
	void DrawCities();
	void HandleEvents();

	static int Create(void*);

	GraphicLibrary& video;
	World const& world;
	Resources const& res;
	void* thread;
	Image* image;
	int sz;
	bool thread_killed;
	std::map<TerrainType, Color> colors;
};

#endif
