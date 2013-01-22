#ifndef UI_DECORENGINE_H
#define UI_DECORENGINE_H

#include "util/defines.h"

class World;
class GraphicLibrary;
class Resources;
class Person;
class UI;

class DecorEngine {
public:
	DecorEngine(const World& world, const GraphicLibrary& video, 
			const Resources& res, const UI& ui)
		: world(world), video(video), res(res), ui(ui) { }
	~DecorEngine();

	void PrepareFrame(int scr_h, int scr_w) const;
	int Next(int y) const;
	void Draw(int y) const;

private:
	const World& world;
	const GraphicLibrary& video;
	const Resources& res;
	const UI& ui;

	DISALLOW_COPY_AND_ASSIGN(DecorEngine);
};

#endif

