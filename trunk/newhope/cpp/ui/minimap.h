#ifndef UI_MINIMAP_H
#define UI_MINIMAP_H

#include "libs/graphiclibrary.h"
#include "world/world.h"

class Minimap {
public:
	Minimap(GraphicLibrary& video, World const& world);
	~Minimap();

	void Reset();
	void Display();

private:
	void KillThread();
};

#endif
