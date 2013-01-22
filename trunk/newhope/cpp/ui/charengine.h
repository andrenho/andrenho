#ifndef UI_CHARENGINE_H
#define UI_CHARENGINE_H

#include <vector>

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

	void PrepareFrame(int scr_h, int scr_w) const;
	int Next(int y) const;
	void Draw(int y) const;

private:
	void DrawPerson(const Person& person) const;

	const World& world;
	const GraphicLibrary& video;
	const Resources& res;
	const UI& ui;

	mutable std::vector<const Person*> people_frame;

	DISALLOW_COPY_AND_ASSIGN(CharEngine);
};

#endif
