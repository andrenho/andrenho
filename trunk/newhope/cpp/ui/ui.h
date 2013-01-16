#ifndef UI_UI_H
#define UI_UI_H

#include "libs/sdl/sdl.h"
#include "ui/minimap.h"
#include "util/point.h"

class World;
class GraphicLibrary;
class Resources;
class TerrainSurface;

class UI {
public:
	UI(World const& world);
	~UI();

	void StartFrame();
	void ProcessEvents();
	void Draw();
	void EndFrame();

	inline bool Active() { return active; }

private:
	void GoTo(Point p);
	void MoveView(int horiz, int vert);

	//World const& world;
	bool active;
	int rx, ry;
	GraphicLibrary* video;
	Resources* res;
	TerrainSurface* terrain_sf;
	Minimap* minimap;
};

#endif
