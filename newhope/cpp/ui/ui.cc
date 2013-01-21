#include "ui/ui.h"

#include <cassert>
#include <vector>

#include "libs/graphiclibrary.h"
#include "ui/resource.h"
#include "ui/terrainsurface.h"
#include "ui/charengine.h"
#include "ui/minimap.h"
#include "util/logger.h"
#include "world/city.h"

#include "SDL.h"

UI::UI(World const& world, GraphicLibrary const& video)
	: world(world), active(true), rx(0), ry(0), 
	  video(video), 
	  res(new Resources(video)),
	  terrain_sf(new TerrainSurface(world, video, *res)),
	  minimap(new Minimap(video, world, *res)), 
	  draw_next_frame(true),
	  char_engine(new CharEngine(world, video, *res, *this)),
	  frame_timer(nullptr)
{
	terrain_sf->Resize(video.Window->w, video.Window->h);
	minimap->Reset();

	//GoTo(world.Hero->Pos);
	GoToScr(Point<int>{3000*32, 3000*32});
	//CenterHero();
}


UI::~UI()
{
	delete char_engine;
	delete minimap;
	delete terrain_sf;
	delete res;
	logger.Debug("UI deleted.");
}


void 
UI::StartFrame()
{
	assert(frame_timer == nullptr);
	frame_timer = video.CreateTimer(1000/30);
}


void 
UI::ProcessEvents()
{
	Event const* event = video.GetEvent();
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
			MoveView(s, 0); break;
		case Key::DOWN:
			MoveView(0, -s);  break;
		case Key::UP:
			MoveView(0, s); break;
		case Key::RIGHT:
			MoveView(-s, 0);  break;
		default:
			logger.Debug("%c %d", key->key, key->key);
		}
	}
		break;
	case Event::RESIZE:
		terrain_sf->Resize(video.Window->w, video.Window->h);
		minimap->Reset();
		draw_next_frame = true;
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
	Rect r(-rx % TerrainSurface::TileSize, 
	       -ry % TerrainSurface::TileSize);
	terrain_sf->Img->Blit(*video.Window, r); // TODO - not always
	logger.DebugFrame("Terrain blit: %d ms", SDL_GetTicks()-t);

//	t = SDL_GetTicks();
//	char_engine->Draw(rx, ry, video.Window->w, video.Window->h);
//	logger.DebugFrame("Characters blit: %d ms", SDL_GetTicks()-t);
	
	t = SDL_GetTicks();
	video.Window->Update();
	logger.DebugFrame("Screen flip: %d ms", SDL_GetTicks()-t);

	draw_next_frame = false;
}


void 
UI::EndFrame()
{
	if(frame_timer->ReachedCountDown())
		logger.Debug("Frame delayed!");
	frame_timer->WaitCountDown();
	delete frame_timer;
	frame_timer = nullptr;
}


void 
UI::MoveView(int horiz, int vert)
{
	Uint32 t = SDL_GetTicks();

	// move center of screen
	rx -= horiz;
	ry -= vert;

	terrain_sf->SetTopLeft(Point<int>((rx/TerrainSurface::TileSize), 
			                 (ry/TerrainSurface::TileSize)));

	draw_next_frame = true;

	logger.DebugFrame("SetTopLeft: %d ms", SDL_GetTicks()-t);
}


template<class T> void 
UI::GoToScr(Point<T> p)
{
	rx = p.x;
	ry = p.y;
	MoveView(0, 0);
}


void
UI::CenterHero()
{
	IPoint src = ConvertToScr(world.Hero->Pos);
	src.x -= video.Window->w / 2;
	src.y -= video.Window->h / 2;
	GoToScr(src);
}


DPoint 
UI::ConvertToTile(IPoint scr) const
{
	return { (-rx + scr.x) / (double)TerrainSurface::TileSize,
		 (-ry + scr.y) / (double)TerrainSurface::TileSize };
}


IPoint 
UI::ConvertToScr(DPoint t) const
{
	return { (int)((-t.x * (double)TerrainSurface::TileSize) + rx),
	         (int)((-t.y * (double)TerrainSurface::TileSize) + ry) };
}
