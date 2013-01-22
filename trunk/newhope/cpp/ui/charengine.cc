#include "ui/charengine.h"

#include <string>
#include <sstream>
using namespace std;

#include "libs/image.h"
#include "libs/graphiclibrary.h"
#include "ui/resource.h"
#include "ui/ui.h"
#include "world/world.h"
#include "world/person.h"

CharEngine::~CharEngine()
{
}


void 
CharEngine::Draw(int scr_h, int scr_w) const
{
	for(const auto& person: world.People) {
		Point<int> p(ui.TileToRel(person->Pos));
		if(p.x >= -TileSize && p.y >= -TileSize 
		&& p.x < scr_w + TileSize && p.y < scr_h + TileSize)
			DrawPerson(*person);
	}
}


void 
CharEngine::DrawPerson(const Person& person) const
{
	// body
	string body("male");

	// clothes
	string clothes("pants");

	// direction
	string direction(1, person.Facing);

	// step
	std::stringstream s;
	s << person.Step() % 8;
	string step(s.str());

	// find position
	Point<int> scr(ui.TileToRel(person.Pos));

	// create image
	string charimage(body + "_" + direction + "_" + step);
	res[charimage]->Blit(*video.Window, Rect(scr.x, scr.y));

	string charclothes(clothes + "_" + direction + "_" + step);
	res[charclothes]->Blit(*video.Window, Rect(scr.x, scr.y));
}
