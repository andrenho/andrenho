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
}


void
Minimap::Reset()
{
	KillThread();
	thread = (void*)SDL_CreateThread(
			(int(*)(void*))&Minimap::Create,
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
Minimap::Create(void* minimap)
{
	Minimap* self = (Minimap*)minimap;
	logger.Debug("Redrawing minimap...");

	// recreate image
	if(self->image)
		delete self->image;
	self->sz = std::min(self->video.Window->w, self->video.Window->h);
	self->image = &self->video.CreateImage(self->sz, self->sz);

	// draw map
	self->DrawMap();
	if(!self->thread_killed)
	{
		self->DrawRivers();
		self->DrawCities();
	}
	logger.Debug("Minimap redrawn.");

	return 0;
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
		}
		delete event;
	}
}
