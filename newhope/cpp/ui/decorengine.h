#ifndef UI_DECORENGINE_H
#define UI_DECORENGINE_H

#include "util/defines.h"
#include "world/world.h"

class GraphicLibrary;
class Resources;
class Person;
class UI;

typedef enum { TREE } ObjType;
struct DecorObject {
	DecorObject(int y, ObjType o, Point<int> tile) : 
		y(y), objType(o), tile(tile) { }
	const int y;
	const ObjType objType;
	const Point<int> tile;
};
struct DecorObjTree : public DecorObject {
	DecorObjTree(int y, ObjType o, Point<int> tile, TreeType type) 
		: DecorObject(y, o, tile), type(type) { }
	const TreeType type;
};

class DecorEngine {
public:
	DecorEngine(const World& world, const GraphicLibrary& video, 
			const Resources& res, const UI& ui)
		: world(world), video(video), res(res), ui(ui) { }
	~DecorEngine();

	void PrepareFrame(int scr_w, int scr_h) const;
	int Next(int y) const;
	void Draw(int y) const;

private:
	void DrawTree(const DecorObjTree* obj) const;

	const World& world;
	const GraphicLibrary& video;
	const Resources& res;
	const UI& ui;

	mutable std::vector<const DecorObject*> obj_frame;

	DISALLOW_COPY_AND_ASSIGN(DecorEngine);
};

#endif

