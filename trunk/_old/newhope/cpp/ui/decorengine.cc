#include "ui/decorengine.h"

#include <climits>
#include <cstdlib>
#include <string>
#include <sstream>
using namespace std;

#include "libs/image.h"
#include "libs/graphiclibrary.h"
#include "ui/resource.h"
#include "ui/ui.h"
#include "world/world.h"
#include "world/person.h"

DecorEngine::~DecorEngine()
{
	for(const auto& obj: obj_frame)
		delete obj;
	obj_frame.clear();
}


void 
DecorEngine::PrepareFrame(int scr_w, int scr_h) const
{
	// clear frame
	for(const auto& obj: obj_frame)
		delete obj;
	obj_frame.clear();

	// add trees
	for(int x(0); x<scr_w; x+=TileSize) {
		for(int y(0); y<scr_h; y+=TileSize) {
			Point<int> tile = ui.RelToTile(Point<int>(x, y));
			TreeType tree = world.Tree(tile);
			if(tree) {
				DecorObject* obj = new DecorObjTree(
						y + 20, ObjType::TREE, tile, tree);
				obj_frame.push_back(obj);
			}
		}
	}

	// add people
	for(const auto& person: world.People) {
		Point<int> p(ui.TileToRel(person->Pos));
		if(p.x >= -TileSize && p.y >= -TileSize 
		&& p.x < scr_w + TileSize && p.y < scr_h + TileSize) {
			DecorObject* obj = new DecorObjPerson(
					p.y, ObjType::PERSON, person);
			obj_frame.push_back(obj);
		}
	}

	// sort frame
	sort(obj_frame.begin(), obj_frame.end(),
	[](const DecorObject* const& d1, const DecorObject* const& d2) -> bool { 
		return d1->y > d2->y;
	});
}


void 
DecorEngine::Draw() const
{
	while(!obj_frame.empty()) {
		if(obj_frame[0]->objType == TREE) {
			DrawTree(static_cast<const DecorObjTree*>(obj_frame[0]));
		} else if(obj_frame[0]->objType == PERSON) {
			DrawPerson(static_cast<const DecorObjPerson*>(
						obj_frame[0])->person);
		}
		delete obj_frame[0];
		obj_frame.erase(obj_frame.begin());
	}
}


void 
DecorEngine::DrawTree(const DecorObjTree* obj) const
{
	const Image* img;
	if(obj->type == TREE_ROUND) {
		img = res["trunk_1"];
	} else if(obj->type == TREE_POINTY) {
		img = res["trunk_2"];
	} else {
		abort();
	}

	Point<int> scr(ui.TileToRel(obj->tile));
	img->Blit(*video.Window, Rect(scr.x-32, scr.y-32));
}


void 
DecorEngine::DrawPerson(const Person* person) const
{
	// body
	string body("male");

	// clothes
	string clothes("pants");

	// direction
	string direction(1, person->Facing);

	// step
	std::stringstream s;
	s << person->Step() % 8;
	string step(s.str());

	// find position
	Point<int> scr(ui.TileToRel(person->Pos));

	// create image
	string charimage(body + "_" + direction + "_" + step);
	res[charimage]->Blit(*video.Window, Rect(scr.x, scr.y));

	string charclothes(clothes + "_" + direction + "_" + step);
	res[charclothes]->Blit(*video.Window, Rect(scr.x, scr.y));
}

