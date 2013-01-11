#include "ui/minimap.h"

#include <algorithm>
#include "SDL.h"

#include "util/logger.h"

Minimap::Minimap(GraphicLibrary& video, World const& world, 
		Resources const& res)
	: video(video), world(world), res(res), thread(NULL), image(NULL), 
	  sz(0), thread_killed(false)
{
	SetupColors();
}


Minimap::~Minimap()
{
	if(image)
		delete image;
}


void
Minimap::SetupColors()
{
	colors[t_WATER] = (Color) { 152, 180, 212 };
	colors[t_DIRT] = (Color) { 0xbe, 0xa3, 0x76 };
	colors[t_EARTH] = (Color) { 0x9e, 0x83, 0x56 };
	colors[t_GRASS] = (Color) { 59, 122, 87 };
	colors[t_ROCK] = (Color) { 0x90, 0x90, 0x90 };
	colors[t_HOTFOREST] = (Color) { 29, 92, 57 };
	colors[t_LAVAROCK] = (Color) { 0x50, 0x50, 0x50 };
	colors[t_SNOW] = (Color) { 0xe0, 0xe0, 0xff };
	colors[t_COLDFOREST] = (Color) { 0, 52, 27 };
	colors[t_INVALID] = (Color) { 0, 0, 0 };
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
	if(thread)
	{
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
	((Minimap*)minimap)->Create();
	return 0;
}


void Minimap::Create()
{
	logger.Debug("Redrawing minimap...");

	// recreate image
	if(image)
		delete image;
	sz = std::min(video.Window->w, video.Window->h) - 250;
	image = &video.CreateImage(sz, sz);

	// draw map
	DrawMap();
	if(!thread_killed)
	{
		DrawRivers();
		DrawCities();
	}
	logger.Debug("Minimap redrawn.");
}


void
Minimap::KillThread()
{
	if(thread)
	{
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
	for(int y = r.y + res.Img("mm_nw")->h; y < r.y + r.h - 60; 
			y += res.Img("mm_w")->h)
	{
		res.Img("mm_w")->Blit(*video.Window, Rect(r.x, y));
		res.Img("mm_e")->Blit(*video.Window, 
				Rect(r.x + r.w - res.Img("mm_e")->w, y));
	}
	for(int x = r.x + res.Img("mm_nw")->w; 
			x < r.x + r.w - res.Img("mm_ne")->w;
			x += res.Img("mm_n")->w)
	{
		res.Img("mm_n")->Blit(*video.Window, Rect(x, r.y));
		res.Img("mm_s")->Blit(*video.Window, 
				Rect(x, r.y + r.h - res.Img("mm_s")->h));
	}

	// corners
	int tr = r.x;
	int dfw = r.w - res.Img("mm_ne")->w,
	    dfh = r.h - res.Img("mm_se")->h;
	res.Img("mm_nw")->Blit(*video.Window, r);
	r.x += dfw;
	res.Img("mm_ne")->Blit(*video.Window, r);
	r.y += dfh;
	res.Img("mm_se")->Blit(*video.Window, r);
	r.x = tr;
	res.Img("mm_sw")->Blit(*video.Window, r);

	// middle
	video.Window->FillBox(r2, (Color){ 210, 183, 119});
}


void
Minimap::DrawMap()
{
	logger.Debug("Drawing biomes...");

	int px, py;
	double x, y, ps = (double)world.w / (double)sz;
	for(x=px=0; x<world.w && px < sz; x+=ps, px++)
	{
		for(y=py=0; y<world.h && py < sz; y+=ps, py++)
		{
			if(thread_killed)
				return;
			TerrainType t = world.Terrain(x, y);
			image->SetPixel(px, py, colors[t]);
		}
	}
}


void
Minimap::DrawRivers()
{
	logger.Debug("Drawing rivers...");

	double ps = (double)world.w / (double)sz;
	for(std::vector<Polygon*>::const_iterator river = world.map->rivers.begin();
			river != world.map->rivers.end(); river++)
		for(unsigned int i=0; i<(*river)->points.size()-1; i++)
		{
			Point p1 = (*river)->points[i];
			Point p2 = (*river)->points[i+1];
			p1 = { (double)p1.x/ps, (double)p1.y/ps };
			p2 = { (double)p2.x/ps, (double)p2.y/ps };
			image->DrawLine(p1, p2, colors[t_WATER], 2);
		}
}


void
Minimap::DrawCities()
{
}


void
Minimap::HandleEvents()
{
	bool map_active = true;
	while(map_active)
	{
		Event const* event = video.GetEvent();
		switch(event->type)
		{
		case Event::CLICK:
			map_active = false;
			break;
		default:
			break;
		}
		delete event;
	}
}
