#ifndef LIBS_IMAGE_H
#define LIBS_IMAGE_H

#include "libs/resource.h"
#include "libs/colors.h"
#include "util/rect.h"
#include "util/point.h"

class Image : public Resource {
public:
	Image(int w, int h) 
		: w(w), h(h) { }
	virtual ~Image() { }

	virtual void SetPixel(int x, int y, Color c) = 0;
	virtual void Blit(Image const& image) const = 0;
	virtual void Blit(Image const& image, Rect const& r) const = 0;
	virtual void Update() = 0;
	virtual void FillBox(Color c) = 0;
	virtual void FillBox(Rect r, Color c) = 0;
	virtual void HollowBox(Rect r, Color c, int width=1);
	virtual void DrawLine(Point p1, Point p2, Color c, int w=1) = 0;

	const int w, h;
};

#endif
