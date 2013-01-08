#ifndef LIBS_LIBS_H
#define LIBS_LIBS_H

#include <string>
#include "libs/rect.h"
#include "libs/image.h"

class GraphicLibrary {
public:
	virtual ~GraphicLibrary() { }
	virtual void StartCountDown(int wait_ms) = 0;
	virtual bool ReachedCountDown() = 0;
	virtual void WaitCountDown() = 0;
	virtual Image& LoadImage(std::string const& filename, Rect const& r) const = 0;
};

#endif
