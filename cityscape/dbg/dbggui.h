#ifndef DBGGUI_H
#define DBGGUI_H

#include "SDL.h"

#include "gui.h"

#define TILE 20

class DebugGUI : public GUI
{
public:
	DebugGUI(City* city) : GUI(city) { }

	bool Startup();
	void Main();

private:
	SDL_Surface* screen;
	Uint32 white, black;
	bool active;

	void UpdateScreen();
	void DrawStructure(Structure* structure);
	void DrawPerson(Person* person);
	void ManageMouseClick(SDL_MouseButtonEvent mb);
	void ManageKeyboard(SDL_KeyboardEvent kb);
	Tile* getHoverTile();
};

#endif

