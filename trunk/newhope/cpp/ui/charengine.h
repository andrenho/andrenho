#ifndef UI_CHARENGINE_H
#define UI_CHARENGINE_H

#include "util/defines.h"

class World;
class GraphicLibrary;
class Resources;
class Person;
class UI;

class CharEngine {
public:
	CharEngine(const World& world, const GraphicLibrary& video, 
			const Resources& res, const UI& ui)
		: world(world), video(video), res(res), ui(ui) { }
	~CharEngine();

	void Draw(int scr_h, int scr_w) const;

private:
	void DrawPerson(const Person& person) const;

	const World& world;
	const GraphicLibrary& video;
	const Resources& res;
	const UI& ui;

	DISALLOW_COPY_AND_ASSIGN(CharEngine);
};

#endif
