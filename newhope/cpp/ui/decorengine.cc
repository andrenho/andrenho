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
}


void 
DecorEngine::PrepareFrame(int scr_h, int scr_w) const
{
}


int 
DecorEngine::Next(int y) const
{
	return INT_MIN;
}


void 
DecorEngine::Draw(int y) const
{
}
