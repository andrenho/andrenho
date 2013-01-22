#ifndef LIBS_RECT_H
#define LIBS_RECT_H

#include "util/defines.h"

class Rect {
public:
	constexpr Rect(int x, int y, int w, int h)
		: x(x), y(y), w(w), h(h) { }

	Rect()
		: x(0), y(0), w(0), h(0) { }
	Rect(int n)
		: x(n), y(0), w(0), h(0) { }
	Rect(int x, int y)
		: x(x), y(y), w(0), h(0) { }

	inline void Add(int x, int y, int w, int h) {
		this->x += x;
		this->y += y;
		this->w += w;
		this->h += h;
	}

	void operator=(const Rect&) {

	}

	int x, y, w, h;

private:
	DISALLOW_COPY_AND_ASSIGN(Rect);
};

#endif
