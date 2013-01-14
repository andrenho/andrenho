#include "ui/ui.h"

#include <vector>

#include "ui/resource.h"
#include "ui/terrainsurface.h"
#include "util/logger.h"

UI::UI(World const& world)
	: /*world(world), */ active(true), rx(0), ry(0), video(new SDL()), 
	  res(new Resources(*video)),
	  terrain_sf(new TerrainSurface(world)),
	  minimap(new Minimap(*video, world, *res))
{
	terrain_sf->Resize(video->Window->w, video->Window->h);
	minimap->Reset();
}


UI::~UI()
{
	delete minimap;
	delete terrain_sf;
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
	std::vector<Rect> rects;
	terrain_sf->AreasToRedraw(rects);

	if(rects.empty())
	{
		Rect r(rx % TerrainSurface::TileSize, 
				ry % TerrainSurface::TileSize);
		terrain_sf->Img->Blit(*video->Window, r);
		// terminal->Draw();
		video->Window->Update();
	}
	else
	{
		// TODO
		abort();
	}
}


void 
UI::EndFrame()
{
//	if(video->ReachedCountDown())
//		logger.Debug("Frame delayed!");
	video->WaitCountDown();
}
