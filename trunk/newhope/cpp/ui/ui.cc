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
	  char_engine(new CharEngine(world, video, *res, *this)),
	  frame_timer(nullptr)
{
	terrain_sf->Resize(video.Window->w, video.Window->h);
	minimap->Reset();

	//GoTo(world.Hero->Pos);
	//GoToScr(Point<int>{3000*32, 3000*32});
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
	ProcessMovementKeys();

	Event const* event = video.GetEvent();
	if(event->type == Event::QUIT)
		active = false;
	else if(event->type == Event::KEY)
	{
		const KeyEvent* key = (const KeyEvent*)event;
		if(key->key == '\t')
			minimap->Display(); 
	}
	else if(event->type == Event::RESIZE)
	{
		terrain_sf->Resize(video.Window->w, video.Window->h);
		minimap->Reset();
	}
	delete event;
}


void 
UI::ProcessMovementKeys()
{
	KeyState state;
	video.GetKeyState(state);
	if(state.Left && state.Up)
		world.Hero->Movement(-1, -1);
	else if(state.Right && state.Up)
		world.Hero->Movement(1, -1);
	else if(state.Up)
		world.Hero->Movement(0, -1);
	else if(state.Left && state.Down)
		world.Hero->Movement(-1, 1);
	else if(state.Right && state.Down)
		world.Hero->Movement(1, 1);
	else if(state.Down)
		world.Hero->Movement(0, 1);
	else if(state.Left)
		world.Hero->Movement(-1, 0);
	else if(state.Right)
		world.Hero->Movement(1, 0);
	else
		world.Hero->Movement(0, 0);
}


void 
UI::Draw()
{
	CenterHero();
	
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

	t = SDL_GetTicks();
	char_engine->Draw(video.Window->w, video.Window->h);
	logger.DebugFrame("Characters blit: %d ms", SDL_GetTicks()-t);
	
	t = SDL_GetTicks();
	video.Window->Update();
	logger.DebugFrame("Screen flip: %d ms", SDL_GetTicks()-t);
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
	IPoint src = TileToScr(world.Hero->Pos);
	src.x -= video.Window->w / 2;
	src.y -= video.Window->h / 2;
	GoToScr(src);
}
