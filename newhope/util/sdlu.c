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
