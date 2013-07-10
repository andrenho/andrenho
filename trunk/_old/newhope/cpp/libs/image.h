#ifndef LIBS_IMAGE_H
#define LIBS_IMAGE_H

#include "libs/resource.h"
#include "libs/colors.h"
#include "util/rect.h"
#include "util/point.h"
#include "util/defines.h"

class Image : public Resource {
public:
	Image(int w, int h) 
		: w(w), h(h) { }
	virtual ~Image() { }

	virtual void SetPixel(int x, int y, Color c) = 0;
	virtual void Blit(const Image& image) const = 0;
	virtual void Blit(const Image& image, const Rect& r) const = 0;
	virtual void Update() = 0;
	virtual void FillBox(Color c) = 0;
	virtual void FillBox(Rect r, Color c) = 0;
	virtual inline void HollowBox(Rect r, Color c, int width=1)
	{
		FillBox(Rect(r.x, r.y, width, r.h), c);
		FillBox(Rect(r.x, r.y, r.w, width), c);
		FillBox(Rect(r.x, r.y+r.h-width, r.w, width), c);
		FillBox(Rect(r.x+r.w-width, r.y, width, r.h), c);
	}
	virtual void DrawLine(Point<int> p1, Point<int> p2, Color c, int w=1) = 0;

	const int w, h;

protected:
	DISALLOW_COPY_AND_ASSIGN(Image);
};

#endif
