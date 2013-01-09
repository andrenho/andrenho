#ifndef LIBS_LIBS_H
#define LIBS_LIBS_H

#include <string>
#include "libs/rect.h"
#include "libs/image.h"
#include "libs/font.h"

class Event {
public:
	enum TypeEvent { NO_EVENT, QUIT, KEY, CLICK, RESIZE };
	Event(enum TypeEvent type) : type(type) { }
	
	const enum TypeEvent type;
};

class KeyEvent : public Event {
public:
	KeyEvent(char key) : Event(KEY), key(key) { }
	const char key;
};

class ClickEvent : public Event {
public:
	enum MouseButton { LEFT, RIGHT, MIDDLE };
	ClickEvent(int x, int y, enum MouseButton button) : Event(CLICK),
			x(x), y(y), button(button) { }

	const int x, y;
	const enum MouseButton button;
};

class GraphicLibrary {
public:
	virtual ~GraphicLibrary() { }

	virtual void StartCountDown(int wait_ms) = 0;
	virtual bool ReachedCountDown() const = 0;
	virtual void WaitCountDown() = 0;

	virtual Image& LoadImage(std::string const& filename, Rect const& r) const = 0;
	virtual Image& CreateImage(int w, int h) const = 0;
	virtual Font& LoadFont(std::string const& filename, int size) const = 0;

	virtual Event const* GetEvent() const = 0;

	mutable Image* Window;
};

#endif
