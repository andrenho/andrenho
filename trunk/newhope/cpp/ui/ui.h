#ifndef UI_UI_H
#define UI_UI_H

#include "libs/sdl/sdl.h"
#include "ui/minimap.h"

class World;
class GraphicLibrary;
class Resources;

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
	World const& world;
	bool active;
	GraphicLibrary* video;
	const Resources* res;
	Minimap* minimap;
};

#endif
