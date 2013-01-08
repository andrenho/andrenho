#ifndef LIBS_RECT_H
#define LIBS_RECT_H

class Rect {
public:
	Rect(int x, int y, int w, int h)
		: x(x), y(y), w(w), h(h) { }

	const int x, y, w, h;
};

#endif
