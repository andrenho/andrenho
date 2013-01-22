#ifndef LIBS_LIBS_H
#define LIBS_LIBS_H

#include <string>
#include "util/rect.h"
#include "libs/image.h"
#include "libs/font.h"
#include "util/defines.h"

class Event {
public:
	enum TypeEvent { NO_EVENT, QUIT, KEY, CLICK, RESIZE };
	explicit Event(enum TypeEvent type) : type(type) { }
	
	const enum TypeEvent type;

private:
	DISALLOW_COPY_AND_ASSIGN(Event);
};


typedef enum Key { UP=256, DOWN, LEFT, RIGHT } Key;

class KeyEvent : public Event {
public:
	explicit KeyEvent(int key) 
		: Event(KEY), key(key) { }
	const int key;

private:
	DISALLOW_COPY_AND_ASSIGN(KeyEvent);
};


struct KeyState {
	bool Shift, Control;
	bool Left, Right, Up, Down;
};


class ClickEvent : public Event {
public:
	enum MouseButton { LEFT, RIGHT, MIDDLE };
	ClickEvent(int x, int y, enum MouseButton button) : Event(CLICK),
			x(x), y(y), button(button) { }

	const int x, y;
	const enum MouseButton button;

private:
	DISALLOW_COPY_AND_ASSIGN(ClickEvent);
};


class Timer {
public:
	explicit Timer(int wait_ms) { }
	virtual ~Timer() { }
	virtual bool ReachedCountDown() const = 0;
	virtual void WaitCountDown() = 0;

private:
	DISALLOW_COPY_AND_ASSIGN(Timer);
};


class GraphicLibrary {
public:
	GraphicLibrary() { }
	virtual ~GraphicLibrary() { }

	virtual Timer* CreateTimer(int wait_ms) const = 0;

	virtual Image* LoadImage(const std::string& filename, const Rect& r) const = 0;
	virtual Image* CreateImage(int w, int h) const = 0;
	virtual Font* LoadFont(const std::string& filename, int size) const = 0;

	virtual const Event* GetEvent() const = 0;
	virtual void GetKeyState(KeyState& state) const = 0;

	mutable Image* Window;

private:
	DISALLOW_COPY_AND_ASSIGN(GraphicLibrary);
};

#endif
