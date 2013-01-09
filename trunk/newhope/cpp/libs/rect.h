#ifndef LIBS_RECT_H
#define LIBS_RECT_H

class Rect {
public:
	Rect(int x, int y, int w, int h)
		: x(x), y(y), w(w), h(h) { }
	Rect(int n)
		: x(n), y(0), w(0), h(0) { }

	void Add(int x, int y, int w, int h);

	int x, y, w, h;
};

#endif
