#include "ui/charengine.h"

#include <string>
using namespace std;

#include "world/world.h"
#include "ui/resource.h"
#include "libs/image.h"
#include "ui/ui.h"

CharEngine::~CharEngine()
{
}


void 
CharEngine::Draw(int scr_x, int scr_y, int scr_h, int scr_w) const
{
	for(auto const& person: world.People)
	{
		/*if(person->Pos.x >= scr_x && person->Pos.y >= scr_y
		&& person->Pos.x < (scr_x+scr_w) 
		&& person->Pos.y < (scr_y+scr_h))*/
			DrawPerson(*person, scr_x, scr_y);
	}
}


void 
CharEngine::DrawPerson(Person const& person, int scr_x, int scr_y) const
{
	// body
	string body("male");

	// clothes
	string clothes("pants");

	// direction
	string direction(1, person.Facing);

	// step
	string step("0");

	// find position
	IPoint scr = ui.ConvertToScr(person.Pos);

	// create image
	string charimage(body + "_" + direction + "_" + step);
	res[charimage]->Blit(*video.Window, Rect(scr.x, scr.y));

	string charclothes(clothes + "_" + direction + "_" + step);
	res[charclothes]->Blit(*video.Window, Rect(scr.x, scr.y));
}
