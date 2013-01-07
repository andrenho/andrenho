#include "sdlu.h"

int inside(int x, int y, SDL_Rect r)
{
	return (x >= r.x && y >= r.y && x < (r.x+r.w) && y < (r.y+r.h));
}


void intersect(SDL_Rect* r, SDL_Rect r2)
{
	if(r->x < r2.x)
	{
		r->w += (r2.x - r->x);
		r->x = r2.x;
	}
	if(r->y < r2.y)
	{
		r->h += (r2.y - r->h);
		r->y = r2.y;
	}
	if((r->x + r->w) > (r2.x + r2.w))
		r->w = (r2.x + r2.w - r->x);
	if((r->y + r->h) > (r2.y + r2.h))
		r->h = (r2.y + r2.h - r->y);
}


void intersect_scr(SDL_Rect* r)
{
	SDL_Surface* scr = SDL_GetVideoSurface();
	SDL_Rect r2 = { 0, 0, scr->w, scr->h };
	intersect(r, r2);
}


void draw_line(SDL_Surface* sf, int x0, int y0, int x1, int y1, Uint32 c)
{
	int dx = abs(x1-x0), sx = x0<x1 ? 1 : -1;
	int dy = abs(y1-y0), sy = y0<y1 ? 1 : -1;
	int err = (dx>dy ? dx : -dy)/2, e2;

	for(;;)
	{
		Uint8 *p = (Uint8*)sf->pixels 
			+ (y0 * sf->pitch)
			+ (x0 * 4);
		*(Uint32*)p = c;

		if(x0 == x1 && y0 == y1)
			break;
		e2 = err;
		if(e2 > -dx)
		{
			err -= dy;
			x0 += sx;
		}
		if(e2 < dy)
		{
			err += dx;
			y0 += sy;
		}
	}
}
