module gui.button;

import derelict.sdl.sdl;

import std.xml;

import gui.defaultgui;


class Buttons
{
	private const int separatorLength;
	
	private Button[] buttons;
	SDL_Surface* sf;
	int w, h;
	
	void opOpAssign(string s)(Button b) if (s == "~")
	{
		buttons ~= b;
		w += b.sf.w;
		if(b.sf.h > h)
			h = b.sf.h;
	}
	
	void addSeparator()
	{
		buttons ~= null;
		w += separatorLength;
	}
	
	void initialize()
	{
		sf = SDL_CreateRGBSurface(SDL_SWSURFACE, w, h, 32, 0, 0, 0, 0);
		int x = 0;
		foreach(Button b; buttons)
		{
			SDL_Rect r = { cast(short) x, 0 };
			SDL_BlitSurface(b.sf, null, sf, &r);
			x += w;
		}
	}
}


class Button
{
	enum State { PRESSED, RELEASED };
	
	private static SDL_Surface*[string] images;
	private static SDL_Surface* imagePressed, imageMiddle, imageUnpressed;
	
	static void loadImages(SDL_Surface*[string] images)
	{
		this.images = images;
		imagePressed = images["buttonpressed"];
		imageMiddle = images["buttonmiddle"];
		imageUnpressed = images["buttonunpressed"];
	}
	
	
	SDL_Surface* sf; 
	string type;
	private State state;
	
	this(Element e)
	{
		assert(e.tag.name == "button");
		type = e.tag.attr["type"];
		sf = SDL_CreateRGBSurface(SDL_SWSURFACE, imageUnpressed.w, imageUnpressed.h, 32, 0, 0, 0, 0);
		setState(State.RELEASED);
	}
	
	
	void setState(Button.State state)
	{
		final switch(state)
		{
			case State.PRESSED:
				SDL_BlitSurface(imagePressed, null, sf, null);
				break;
			case State.RELEASED:
				SDL_BlitSurface(imageUnpressed, null, sf, null);
				break;
		}
	}
}