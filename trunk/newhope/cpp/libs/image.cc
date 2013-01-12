#include "libs/image.h"

void 
Image::HollowBox(Rect r, Color c, int width)
{
	FillBox(Rect(r.x, r.y, width, r.h), c);
	FillBox(Rect(r.x, r.y, r.w, width), c);
	FillBox(Rect(r.x, r.y+r.h-width, r.w, width), c);
	FillBox(Rect(r.x+r.w-width, r.y, width, r.h), c);
}
