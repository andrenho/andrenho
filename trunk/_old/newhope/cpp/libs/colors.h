#ifndef COLORS_H
#define COLORS_H

typedef struct Color {
	Color() : r(0), g(0), b(0) { }
	Color(int r, int g, int b) : r(r), g(g), b(b) { }
	int r, g, b;
} Color;

#endif
