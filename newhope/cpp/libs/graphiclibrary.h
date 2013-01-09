#ifndef LIBS_LIBS_H
#define LIBS_LIBS_H

#include <string>
#include "libs/rect.h"
#include "libs/image.h"
#include "libs/font.h"

class GraphicLibrary {
public:
	virtual ~GraphicLibrary() { }
	virtual void StartCountDown(int wait_ms) = 0;
	virtual bool ReachedCountDown() const = 0;
	virtual void WaitCountDown() = 0;
	virtual Image& LoadImage(std::string const& filename, Rect const& r) const = 0;
	virtual Image& CreateImage(int w, int h) const = 0;
	virtual Font& LoadFont(std::string const& filename, int size) const = 0;

	Image* Window;
};

#endif
