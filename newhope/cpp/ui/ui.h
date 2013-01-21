#ifndef UI_UI_H
#define UI_UI_H

#include "util/point.h"

class World;
class GraphicLibrary;
class Resources;
class TerrainSurface;
class CharEngine;
class GraphicLibrary;
class Minimap;
class Timer;

class UI {
public:
	UI(World const& world, GraphicLibrary const& video);
	~UI();

	void StartFrame();
	void ProcessEvents();
	void Draw();
	void EndFrame();

	void ConvertToTile(int scr_x, int scr_y, double& tx, double& ty) const;
	void ConvertToScr(double tx, double ty, int& scr_x, int& scr_y) const;

	inline bool Active() { return active; }

private:
	void CenterHero();
	void GoTo(IPoint p);
	void MoveView(int horiz, int vert);


	World const& world;
	bool active;
	int rx, ry;
	GraphicLibrary const& video;
	Resources* res;
	TerrainSurface* terrain_sf;
	Minimap* minimap;
	bool draw_next_frame;
	CharEngine const* char_engine;
	Timer* frame_timer;
};

#endif
