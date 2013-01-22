#ifndef LIBS_RECT_H
#define LIBS_RECT_H

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

	/*Rect& operator=(const Rect& other) {
		if(this != &other) {
			x = other.x;
			y = other.y;
			w = other.w;
			h = other.h;
		}
		return *this;
	}*/

	constexpr Rect(const Rect& other) :
		x(other.x), y(other.y), w(other.w), h(other.h) { }

	int x, y, w, h;

private:
	Rect& operator=(const Rect& other); // disallow assignment
};

#endif
