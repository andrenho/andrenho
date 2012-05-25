#ifndef UI_H
#define UI_H

#include "SDL.h"

class City;

class UI
{
public:
	explicit UI(City const& city)
		: city(city), active(true), zoom(20) { }
	~UI();

	bool Active();
	void Init();
	void Draw();
	void Input();
	void Wait();

private:
	City const& city;
	SDL_Surface* screen;
	bool active;
	int zoom;

	void InitColors();
	void Rect(int x, int y, int w, int h, int fg=BLACK, int bg=-1);

	typedef enum {
		BLACK, WHITE, CYAN
	} Colors;
};

#endif
