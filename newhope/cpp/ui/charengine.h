#ifndef UI_CHARENGINE_H
#define UI_CHARENGINE_H

class World;
class GraphicLibrary;
class Resources;
class Person;
class UI;

class CharEngine {
public:
	CharEngine(World const& world, GraphicLibrary const& video, 
			Resources const& res, UI const& ui)
		: world(world), video(video), res(res), ui(ui) { }
	~CharEngine();

	void Draw(int scr_x, int scr_y, int scr_h, int scr_w) const;

private:
	void DrawPerson(Person const& person, int scr_x, int scr_y) const;

	World const& world;
	GraphicLibrary const& video;
	Resources const& res;
	UI const& ui;
};

#endif
