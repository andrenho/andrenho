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
	  minimap(new Minimap(*video, world, *res)), draw_next_frame(true)
{
	terrain_sf->Resize(video->Window->w, video->Window->h);
	minimap->Reset();

	//GoTo(world.map->roads[3]->points[0]);
	//GoTo(world.map->roads[12]->points[0]);
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
	video->StartCountDown(1000/30);
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
			s = 16;
		else if(key->Control)
			s = 150;
		switch(key->key)
		{
		case '\t':
			minimap->Display(); 
			draw_next_frame = true;
			break;
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
	if(!draw_next_frame)
		return;

	Uint32 t = SDL_GetTicks();

	std::vector<Rect> rects;
	terrain_sf->RedrawImg(rects);
	assert(terrain_sf->Img);

	logger.DebugFrame("---------------");
	logger.DebugFrame("New Frame");
	logger.DebugFrame("---------------");
	logger.DebugFrame("Tiles redrawn: %d tiles", rects.size());
	logger.DebugFrame("Terrain redraw: %d ms", SDL_GetTicks()-t);

	t = SDL_GetTicks();
	Rect r(rx % TerrainSurface::TileSize, 
			ry % TerrainSurface::TileSize);
	terrain_sf->Img->Blit(*video->Window, r); // TODO - not always
	logger.DebugFrame("Terrain blit: %d ms", SDL_GetTicks()-t);
	
	t = SDL_GetTicks();
	video->Window->Update();
	logger.DebugFrame("Screen flip: %d ms", SDL_GetTicks()-t);

	draw_next_frame = false;
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
	Uint32 t = SDL_GetTicks();

	// move center of screen
	rx += horiz;
	ry += vert;

	terrain_sf->SetTopLeft(-(rx/TerrainSurface::TileSize), 
			-(ry/TerrainSurface::TileSize));

	draw_next_frame = true;

	logger.DebugFrame("SetTopLeft: %d ms", SDL_GetTicks()-t);
}


void 
UI::GoTo(Point p)
{
	rx = -TerrainSurface::TileSize * p.x;
	ry = -TerrainSurface::TileSize * p.y;
	MoveView(0, 0);
}
