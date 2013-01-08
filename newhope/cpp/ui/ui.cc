#include "ui/ui.h"

#include "ui/resource.h"
#include "util/logger.h"

UI::UI(World const& world)
	: world(world), active(true) 
{ 
	video = new SDL();
	res = new Resources(*video);
}


UI::~UI()
{
	delete res;
	delete video;
}


void 
UI::StartFrame()
{
	video->StartCountDown(1000/60);
}


void 
UI::ProcessEvents()
{
	active = false;
}


void 
UI::Draw()
{
}


void 
UI::EndFrame()
{
	if(video->ReachedCountDown())
		logger.Debug("Frame delayed!");
	video->WaitCountDown();
}
