#include "dbggui.h"

#define FPS 30

bool
DebugGUI::Startup()
{
	if(SDL_Init(SDL_INIT_VIDEO) == -1)
		return false;
	screen = SDL_SetVideoMode(550, 300, 0, SDL_SWSURFACE);
	if(!screen)
		return false;
	white = SDL_MapRGB(screen->format, 255, 255, 255);
	black = SDL_MapRGB(screen->format, 0, 0, 0);
	SDL_FillRect(screen, NULL, white);
	SDL_Flip(screen);

	return true;
}


void
DebugGUI::Main()
{
	active = true;
	SDL_Event e;

	while(active)
	{	
		UpdateScreen();

		Uint32 time = SDL_GetTicks();
		while(SDL_PollEvent(&e))
			switch(e.type)
			{
				case SDL_QUIT:
					active = false;
					break;
				case SDL_KEYDOWN:
					ManageKeyboard(e.key);
					break;
				case SDL_MOUSEBUTTONDOWN:
					ManageMouseClick(e.button);
					break;
			}
		while(SDL_GetTicks() < (time + 1000/FPS))
			;
	}
}


void 
DebugGUI::ManageMouseClick(SDL_MouseButtonEvent mb)
{
	(void)mb;
}


void 
DebugGUI::ManageKeyboard(SDL_KeyboardEvent kb)
{
	Tile* t;

	switch(kb.keysym.sym)
	{
		// quit
		case SDLK_q: 
			active = false;
			break;

		// build low class housing
		case SDLK_l:
			t = getHoverTile();
			if(t)
				city->BuildResidence(t->x, t->y, false,
						ResidentialInfo::LOW,
						ResidentialInfo::LOW_D);
			break;

		default:
			break;
	}
}


Tile*
DebugGUI::getHoverTile()
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	
	return city->getTile(x / TILE, y / TILE);
}
