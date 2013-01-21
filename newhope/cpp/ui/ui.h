#ifndef UI_UI_H
#define UI_UI_H

#include "ui/terrainsurface.h"
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

	template<typename T> Point<int> TileToScr(Point<T> t) const
	{
		return { (int)((t.x * (double)TerrainSurface::TileSize)),
			 (int)((t.y * (double)TerrainSurface::TileSize)) };
	}


	template<typename T> Point<int> TileToRel(Point<T> t) const
	{
		return { (int)((t.x * (double)TerrainSurface::TileSize)) - rx,
			 (int)((t.y * (double)TerrainSurface::TileSize)) - ry};
	}

	inline bool Active() { return active; }

private:
	void ProcessMovementKeys();

	void CenterHero();
	template<class T> void GoToScr(Point<T> p);
	void MoveView(int horiz, int vert);


	World const& world;
	bool active;
	int rx, ry;
	GraphicLibrary const& video;
	Resources* res;
	TerrainSurface* terrain_sf;
	Minimap* minimap;
	CharEngine const* char_engine;
	Timer* frame_timer;
};

#endif
