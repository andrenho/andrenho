#include "ui/ui.h"

#include <cassert>
#include <vector>

#include "libs/graphiclibrary.h"
#include "ui/resource.h"
#include "ui/terrainsurface.h"
#include "util/logger.h"

UI::UI(World const& world)
	: /*world(world), */ active(true), rx(0), ry(0), video(new SDL()), 
	  res(new Resources(*video)),
	  terrain_sf(new TerrainSurface(world, *video, *res)),
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
		int s = 1;
		const KeyEvent* key = (const KeyEvent*)event;
		if(key->Shift)
			s = 10;
		else if(key->Control)
			s = 40;
		switch(key->key)
		{
		case '\t':
			minimap->Display(); break;
		case Key::LEFT:
			MoveView(-s, 0); break;
		case Key::DOWN:
			MoveView(0, s);  break;
		case Key::UP:
			MoveView(0, -s); break;
		case Key::RIGHT:
			MoveView(s, 0);  break;
		default:
			logger.Debug("%c %d", key->key, key->key);
		}
	}
		break;
	case Event::RESIZE:
		terrain_sf->Resize(video->Window->w, video->Window->h);
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
	assert(terrain_sf->Img);

	std::vector<Rect> rects;
	terrain_sf->AreasToRedraw(rects);

	if(rects.empty())
	{
		Rect r(rx % TerrainSurface::TileSize, 
				ry % TerrainSurface::TileSize);
		terrain_sf->Img->Blit(*video->Window, r);
		// terminal->Draw();
		//video->Window->FillBox(Color { 255, 255, 255 });
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
	if(video->ReachedCountDown())
		logger.Debug("Frame delayed!");
	video->WaitCountDown();
}


void 
UI::MoveView(int horiz, int vert)
{
	// move center of screen
	rx += horiz;
	ry += vert;

	terrain_sf->SetTopLeft(-(rx/TerrainSurface::TileSize), 
			-(ry/TerrainSurface::TileSize));
}
