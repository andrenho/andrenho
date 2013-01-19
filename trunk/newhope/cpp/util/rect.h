#ifndef LIBS_RECT_H
#define LIBS_RECT_H

class Rect {
public:
	constexpr Rect(int x, int y, int w, int h)
		: x(x), y(y), w(w), h(h) { }

	Rect()
		: x(0), y(0), w(0), h(0) { }
	//Rect(int x, int y, int w, int h)
	//	: x(x), y(y), w(w), h(h) { }
	Rect(int n)
		: x(n), y(0), w(0), h(0) { }
	Rect(int x, int y)
		: x(x), y(y), w(0), h(0) { }

	void Add(int x, int y, int w, int h);

	int x, y, w, h;
};

#endif
