#include "ui/minimap.h"

#include <algorithm>
using namespace std;

#include "SDL.h"

#include "libs/image.h"
#include "libs/graphiclibrary.h"
#include "ui/resource.h"
#include "util/logger.h"
#include "util/polygon.h"
#include "world/city.h"
#include "world/mapbuild.h"

Minimap::Minimap(const GraphicLibrary& video, const World& world, 
		const Resources& res)
	: video(video), world(world), res(res), thread(nullptr), image(nullptr), 
	  sz(0), thread_killed(false)
{
	SetupColors();
}


Minimap::~Minimap()
{
	KillThread();
	if(image)
		delete image;
}


void
Minimap::SetupColors()
{
	colors[t_WATER] = Color( 152, 180, 212 );
	colors[t_DIRT] = Color( 0xbe, 0xa3, 0x76 );
	colors[t_EARTH] = Color( 0x9e, 0x83, 0x56 );
	colors[t_GRASS] = Color( 59, 122, 87 );
	colors[t_ROCK] = Color( 0x90, 0x90, 0x90 );
	colors[t_HOTFOREST] = Color( 29, 92, 57 );
	colors[t_LAVAROCK] = Color( 0x50, 0x50, 0x50 );
	colors[t_SNOW] = Color( 0xe0, 0xe0, 0xff );
	colors[t_COLDFOREST] = Color( 0, 52, 27 );
}


void
Minimap::Reset()
{
	KillThread();
	thread = (void*)SDL_CreateThread(
			(int(*)(void*))&Minimap::CreationThread,
			(void*)this);
}


void
Minimap::Display()
{
	// draw paper
	DrawPaper();
	video.Window->Update();

	// wait for thread to finish
	if(thread) {
		int n;
		SDL_WaitThread((SDL_Thread*)thread, &n);
		thread = 0;
	}

	// draw map
	Rect r( (video.Window->w/2) - (sz/2),
		(video.Window->h/2) - (sz/2),
		sz, sz);
	image->Blit(*video.Window, r);
	video.Window->Update();

	// handle events
	HandleEvents();
}


int
Minimap::CreationThread(void* minimap)
{
	static_cast<Minimap*>(minimap)->Create();
	return 0;
}


void Minimap::Create()
{
	logger.Debug("Redrawing minimap...");

	// recreate image
	if(image)
		delete image;
	sz = min(video.Window->w, video.Window->h) - 250;
	image = video.CreateImage(sz, sz);

	// draw map
	DrawMap();
	if(!thread_killed) {
		DrawRivers();
		DrawCities();
	}
	logger.Debug("Minimap redrawn.");
}


void
Minimap::KillThread()
{
	if(thread) {
		int n;
		thread_killed = 1;
		SDL_WaitThread((SDL_Thread*)thread, &n);
		thread = 0;
		logger.Debug("Minimap thread killed.");
	}
	thread_killed = 0;
}


void
Minimap::DrawPaper()
{
	Rect r( (video.Window->w/2) - (sz/2),
		(video.Window->h/2) - (sz/2),
		sz, sz);
	Rect r2(r.x - 20, r.y - 20, r.w + 40, r.h + 40);
	r.Add(-60, -85, 120, 170);

	// laterals
	for(int y(r.y + res["mm_nw"]->h); y < r.y + r.h - 60; 
			y += res["mm_w"]->h) {
		res["mm_w"]->Blit(*video.Window, Rect(r.x, y));
		res["mm_e"]->Blit(*video.Window, 
				Rect(r.x + r.w - res["mm_e"]->w, y));
	}
	for(int x(r.x + res["mm_nw"]->w); 
			x < r.x + r.w - res["mm_ne"]->w;
			x += res["mm_n"]->w) {
		res["mm_n"]->Blit(*video.Window, Rect(x, r.y));
		res["mm_s"]->Blit(*video.Window, 
				Rect(x, r.y + r.h - res["mm_s"]->h));
	}

	// corners
	int tr(r.x);
	int dfw(r.w - res["mm_ne"]->w),
	    dfh(r.h - res["mm_se"]->h);
	res["mm_nw"]->Blit(*video.Window, r);
	r.x += dfw;
	res["mm_ne"]->Blit(*video.Window, r);
	r.y += dfh;
	res["mm_se"]->Blit(*video.Window, r);
	r.x = tr;
	res["mm_sw"]->Blit(*video.Window, r);

	// middle
	video.Window->FillBox(r2, Color(210, 183, 119));
}


void
Minimap::DrawMap()
{
	logger.Debug("Drawing biomes...");

	int px, py;
	double x, y, ps = (double)world.w / (double)sz;
	for(x=px=0; x<world.w && px < sz; x+=ps, px++) {
		for(y=py=0; y<world.h && py < sz; y+=ps, py++) {
			if(thread_killed) {
				return;
			}
			TerrainType t = world.Terrain(Point<int>(x, y), false);
			image->SetPixel(px, py, colors[t]);
		}
	}
}


void
Minimap::DrawRivers()
{
	logger.Debug("Drawing lava...");
	for(const auto& lavapath: world.map->lava)
		DrawPath(lavapath->points, Color(0xcf, 0x10, 0x20));

	logger.Debug("Drawing rivers...");
	for(const auto& river: world.map->rivers)
		DrawPath(river->points, colors[t_WATER]);

	logger.Debug("Drawing roads...");
	for(const auto& road: world.map->roads)
		DrawPath(road->points, Color(0, 0, 0));
}


void 
Minimap::DrawPath(vector<Point<int>>& points, Color c)
{
	double ps = double(world.w) / double(sz);
	Point<int> p2 = Point<int>(-1, -1);
	for(const auto& p1: points) {
		if(p2 == Point<int>(-1, -1)) {
			p2 = Point<int>(p1.x, p1.y);
			continue;
		}

		Point<int> pa(int(double(p1.x)/ps), 
		              int(double(p1.y)/ps));
		Point<int> pb(int(double(p2.x)/ps), 
		              int(double(p2.y)/ps));
		image->DrawLine(pa, pb, c, 2);

		p2 = p1;
	}
}


void
Minimap::DrawCities()
{
	double ps = (double)world.w / (double)sz;
	for(const auto& city : world.map->cities) {
		Point<int> p = city->pos;
		Color c(128, 0, 0);
		image->HollowBox(Rect((p.x/ps)-6, (p.y/ps)-6, 12, 12), c);
		image->FillBox(Rect((p.x/ps)-4, (p.y/ps)-4, 8, 8), c);
	}
}


void
Minimap::HandleEvents()
{
	bool map_active = true;
	while(map_active) {
		const Event* event = video.GetEvent();
		if(event->type == Event::CLICK) {
			map_active = false;
		}
		delete event;
	}
}
