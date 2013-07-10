#ifndef UI_DECORENGINE_H
#define UI_DECORENGINE_H

#include "util/defines.h"
#include "world/world.h"

class GraphicLibrary;
class Resources;
class Person;
class UI;

typedef enum { TREE, PERSON } ObjType;
struct DecorObject {
	DecorObject(int y, ObjType o) : 
		y(y), objType(o) { }
	const int y;
	const ObjType objType;
};
struct DecorObjPerson : public DecorObject {
	DecorObjPerson(int y, ObjType o, const Person* person) 
		: DecorObject(y, o), person(person) { }
	const Person* person;
};
struct DecorObjTree : public DecorObject {
	DecorObjTree(int y, ObjType o, Point<int> tile, TreeType type) 
		: DecorObject(y, o), tile(tile), type(type) { }
	const Point<int> tile;
	const TreeType type;
};

class DecorEngine {
public:
	DecorEngine(const World& world, const GraphicLibrary& video, 
			const Resources& res, const UI& ui)
		: world(world), video(video), res(res), ui(ui) { }
	~DecorEngine();

	void PrepareFrame(int scr_w, int scr_h) const;
	void Draw() const;

private:
	void DrawTree(const DecorObjTree* obj) const;
	void DrawPerson(const Person* person) const;

	const World& world;
	const GraphicLibrary& video;
	const Resources& res;
	const UI& ui;

	mutable std::vector<const DecorObject*> obj_frame;

	DISALLOW_COPY_AND_ASSIGN(DecorEngine);
};

#endif

