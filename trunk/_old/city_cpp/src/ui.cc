#include "ui.h"

#include <string>
#include <vector>
#include <iostream>
using namespace std;

#include "building.h"
#include "city.h"

void 
UI::Init()
{
	if(SDL_Init(SDL_INIT_VIDEO) == -1)
		throw string(SDL_GetError());
	
	screen = SDL_SetVideoMode(400, 300, 8, SDL_SWSURFACE);
	if(!screen)
		throw string(SDL_GetError());

	InitColors();
	SDL_FillRect(screen, NULL, WHITE);
	SDL_Flip(screen);
}


UI::~UI()
{
	if(screen)
		SDL_FreeSurface(screen);
	SDL_Quit();
}


bool
UI::Active()
{
	return active;
}


void 
UI::Draw()
{
	SDL_FillRect(screen, NULL, WHITE);
	for(vector<Building*>::const_iterator bi = city.Buildings()->begin();
			bi != city.Buildings()->end(); bi++)
	{
		Rect((*bi)->x * zoom, (*bi)->y * zoom, (*bi)->w * zoom, (*bi)->h * zoom);
	}
	for(vector<Person*>::const_iterator pi = city.People()->begin();
			pi != city.People()->end(); pi++)
	{
		Rect(int((*pi)->X() * float(zoom)), int((*pi)->Y() * float(zoom)), 
				zoom/4, zoom/4, BLACK, CYAN);
	}
	SDL_Flip(screen);
}


void 
UI::Input()
{
	SDL_Event e;

	while(SDL_PollEvent(&e))
		switch(e.type)
		{
			case SDL_QUIT:
				active = false;
				break;
		}
}


void 
UI::Wait()
{
}


void 
UI::Rect(int x, int y, int w, int h, int fg, int bg)
{
	if(bg != -1)
	{
		SDL_Rect r = { x+1, y+1, w-2, h-2 };
		SDL_FillRect(screen, &r, bg);
	}

	SDL_Rect r = { x, y, 1, h };
	SDL_FillRect(screen, &r, fg);
	r = (SDL_Rect) { x, y, w, 1 };
	SDL_FillRect(screen, &r, fg);
	r = (SDL_Rect) { x+w-1, y, 1, h };
	SDL_FillRect(screen, &r, fg);
	r = (SDL_Rect) { x, y+h-1, w, 1 };
	SDL_FillRect(screen, &r, fg);
}


void UI::InitColors()
{
	SDL_Color colors[256];
	for(int i=0; i<256; i++)
		colors[i] = (SDL_Color) { 0, 0, 0 };

	colors[BLACK] = (SDL_Color) {   0,   0,   0 };
	colors[WHITE] = (SDL_Color) { 255, 255, 255 };
	colors[CYAN] =  (SDL_Color) {   0, 255, 255 };

	SDL_SetColors(screen, colors, 0, 256);
}
