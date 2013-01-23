#include "ui/decorengine.h"

#include <climits>
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
						y + 56, ObjType::TREE, tile, tree);
				obj_frame.push_back(obj);
			}
		}
	}

	// sort frame
	sort(obj_frame.begin(), obj_frame.end(),
	[](const DecorObject* const& d1, const DecorObject* const& d2) -> bool { 
		return d1->y > d2->y;
	});
}


int 
DecorEngine::Next(int y) const
{
	if(!obj_frame.empty()) {
		return obj_frame[0]->y;
	}
	return INT_MIN;
}


void 
DecorEngine::Draw(int y) const
{
	if(obj_frame.empty()) {
		abort();
	}

	double ny = obj_frame[0]->y;
	while(!obj_frame.empty() && obj_frame[0]->y == ny) {
		DrawTree(static_cast<const DecorObjTree*>(obj_frame[0]));
		delete obj_frame[0];
		obj_frame.erase(obj_frame.begin());
	}
}


void 
DecorEngine::DrawTree(const DecorObjTree* obj) const
{
}
