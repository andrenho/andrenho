#ifndef UI_UI_H
#define UI_UI_H

#include "util/defines.h"
#include "util/point.h"

class World;
class GraphicLibrary;
class Resources;
class TerrainSurface;
class DecorEngine;
class GraphicLibrary;
class Minimap;
class Timer;
class TerrainSurface;

class UI {
public:
	UI(const World& world, const GraphicLibrary& video);
	~UI();

	void StartFrame();
	void ProcessEvents();
	void Draw();
	void EndFrame();

	template<typename T> Point<int> TileToScr(Point<T> t) const
	{
		return { (int)((t.x * (double)TileSize)),
			 (int)((t.y * (double)TileSize)) };
	}


	template<typename T> Point<int> TileToRel(Point<T> t) const
	{
		return { (int)((t.x * (double)TileSize)) - rx,
			 (int)((t.y * (double)TileSize)) - ry };
	}


	template<typename T> Point<double> RelToTile(Point<T> t) const
	{
		return { (t.x + rx) / (double)TileSize,
			 (t.y + ry) / (double)TileSize };
	}

	inline bool Active() { return active; }

private:
	void ProcessMovementKeys();

	void CenterHero();
	template<class T> void GoToScr(Point<T> p);
	void MoveView(int horiz, int vert);


	const World& world;
	bool active;
	int rx, ry;
	const GraphicLibrary& video;
	Resources* res;
	TerrainSurface* terrain_sf;
	Minimap* minimap;
	const DecorEngine* decor_engine;
	Timer* frame_timer;

	DISALLOW_COPY_AND_ASSIGN(UI);
};

#endif
