#include "libs/rect.h"

void 
Rect::Add(int x, int y, int w, int h)
{
	this->x += x;
	this->y += y;
	this->w += w;
	this->h += h;
}
