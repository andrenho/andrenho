#include "ui/ui.h"

#include "ui/resource.h"
#include "util/logger.h"

UI::UI(World const& world)
	: world(world), active(true), video(new SDL()), 
	  res(new Resources(*video)),
	  minimap(new Minimap(*video, world, *res))
{
	minimap->Reset();
}


UI::~UI()
{
	delete minimap;
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
	Event const* event = video->GetEvent();
	switch(event->type)
	{
	case Event::QUIT:
		active = false;
		break;
	case Event::KEY:
	{
		const KeyEvent* key = (const KeyEvent*)event;
		switch(key->key)
		{
		case '\t':
			minimap->Display();
			break;
		}
	}
		break;
	case Event::RESIZE:
		minimap->Reset();
		break;
	default:
		break;
	}
	delete event;
}


void 
UI::Draw()
{
	video->Window->FillBox(Color { 255, 255, 255 });
	video->Window->Update();
}


void 
UI::EndFrame()
{
	if(video->ReachedCountDown())
		logger.Debug("Frame delayed!");
	video->WaitCountDown();
}
