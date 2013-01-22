#include "ui/ui.h"

#include <cassert>
#include <vector>
using namespace std;

#include "libs/graphiclibrary.h"
#include "ui/resource.h"
#include "ui/terrainsurface.h"
#include "ui/charengine.h"
#include "ui/minimap.h"
#include "util/logger.h"
#include "world/city.h"
#include "world/person.h"

#include "SDL.h"

UI::UI(const World& world, const GraphicLibrary& video)
	: world(world), active(true), rx(0), ry(0), video(video), 
	  res(new Resources(video)),
	  terrain_sf(new TerrainSurface(world, video, *res)),
	  minimap(new Minimap(video, world, *res)), 
	  char_engine(new CharEngine(world, video, *res, *this)),
	  frame_timer(nullptr)
{
	terrain_sf->Resize(video.Window->w, video.Window->h);
	minimap->Reset();
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

	const Event* event(video.GetEvent());
	if(event->type == Event::QUIT) {
		active = false;
	} else if(event->type == Event::KEY) {
		const KeyEvent* key = (const KeyEvent*)event;
		if(key->key == '\t')
			minimap->Display(); 
	} else if(event->type == Event::RESIZE) {
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
	
	vector<Rect> rects;
	terrain_sf->RedrawImg(rects);
	assert(terrain_sf->Img);

	Rect r(-rx % TileSize, 
	       -ry % TileSize);
	terrain_sf->Img->Blit(*video.Window, r); // TODO - not always

	char_engine->Draw(video.Window->w, video.Window->h);
	
	video.Window->Update();
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
	// move center of screen
	rx -= horiz;
	ry -= vert;

	terrain_sf->SetTopLeft(Point<int>((rx/TileSize), 
			                 (ry/TileSize)));
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
	Point<int> src(TileToScr(world.Hero->Pos));
	src.x -= video.Window->w / 2;
	src.y -= video.Window->h / 2;
	GoToScr(src);
}
