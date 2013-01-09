#include "ui/minimap.h"

#include <algorithm>
#include "SDL.h"

#include "util/logger.h"

Minimap::Minimap(GraphicLibrary& video, World const& world, Resources const& res)
	: video(video), world(world), res(res), thread(NULL), image(NULL), sz(0), 
	  last_w(0), last_h(0), thread_killed(false)
{
	SetupColors();
}


Minimap::~Minimap()
{
	if(image)
		delete image;
}


#include<iostream>
void
Minimap::SetupColors()
{
	colors[t_WATER] = (Color) { 152, 180, 212 };
}


void
Minimap::Reset()
{
	KillThread();
	//thread = (void*)SDL_CreateThread((int(*)(void*))&Minimap::Create, 0);
	Create(0);
}


void
Minimap::Display()
{
	DrawPaper();
	video.Window->Update();

	Rect r( (video.Window->w/2) - (sz/2),
		(video.Window->h/2) - (sz/2),
		sz, sz);
	image->Blit(*video.Window, r);
	video.Window->Update();
	SDL_Delay(2000);
}


int
Minimap::Create(void* nothing)
{
	logger.Debug("Redrawing minimap...");

	// recreate image
	if(image)
		delete image;
	sz = std::min(video.Window->w, video.Window->h);
	image = &video.CreateImage(sz, sz);

	// save window size
	last_w = video.Window->w;
	last_h = video.Window->h;

	// draw map
	DrawMap();
	if(!thread_killed)
	{
		DrawRivers();
		DrawCities();
	}
	logger.Debug("Minimap redrawn.");

	return 0;
}


void
Minimap::KillThread()
{

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
	const Image* img = res.Img("mm_n");
	/*
	for(int y=r.y + res.Img("mm_n")->h; y < r.y + r.h - 60; 
			y += res.Img("mm_w")->h)
		;*/

	/*
	// laterals
	int x, y;
	SDL_Surface *mm_n = res("mm_n"), *mm_w = res("mm_w");
	for(y=r.y+res("mm_nw")->h; y<r.y+r.h-60; y+=mm_w->h)
	{
		SDL_BlitSurface(mm_w, NULL, ui->screen, &(SDL_Rect){ r.x, y });
		SDL_BlitSurface(res("mm_e"), NULL, ui->screen, &(SDL_Rect){ 
				r.x + r.w - res("mm_e")->w, y });
	}
	for(x=r.x+res("mm_nw")->w; x<r.x+r.w-res("mm_ne")->w; x+=mm_n->w)
	{
		SDL_BlitSurface(mm_n, NULL, ui->screen, &(SDL_Rect){ x, r.y });
		SDL_BlitSurface(res("mm_s"), NULL, ui->screen, &(SDL_Rect){ 
				x, r.y + r.h - res("mm_s")->h });
	}

	// borders
	int tr = r.x;
	int dfw = r.w - res("mm_ne")->w,
	    dfh = r.h - res("mm_se")->h;
	SDL_BlitSurface(res("mm_nw"), NULL, ui->screen, &r);
	r.x += dfw;
	SDL_BlitSurface(res("mm_ne"), NULL, ui->screen, &r);
	r.y += dfh;
	SDL_BlitSurface(res("mm_se"), NULL, ui->screen, &r);
	r.x = tr;
	SDL_BlitSurface(res("mm_sw"), NULL, ui->screen, &r);

	// middle
	SDL_FillRect(ui->screen, &r2, 
			SDL_MapRGB(ui->screen->format, 210, 183, 119));
			*/
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
//			if(mm->killthread)
//				return;
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
