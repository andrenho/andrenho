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
        uint magenta = SDL_MapRGB(sf.format, 255, 0, 255);
        SDL_FillRect(sf, null, magenta);
        SDL_SetColorKey(sf, SDL_SRCCOLORKEY, magenta);

		int x = 0;
		foreach(Button b; buttons)
		{
			SDL_Rect r = { cast(short) x, 0 };
			SDL_BlitSurface(b.sf, null, sf, &r);
			x += w;
		}
	}
	
	void click(short x, short y)
	{
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
	
	
	SDL_Surface* sf, image;
	string type;
	private State state;
	
	this(Element e)
	{
		assert(e.tag.name == "button");
		type = e.tag.attr["type"];
        image = images[e.tag.attr["image"]];
		sf = SDL_CreateRGBSurface(SDL_SWSURFACE, imageUnpressed.w, imageUnpressed.h, 32, 0, 0, 0, 0);
        uint magenta = SDL_MapRGB(sf.format, 255, 0, 255);
        SDL_FillRect(sf, null, magenta);
        SDL_SetColorKey(sf, SDL_SRCCOLORKEY, magenta);
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
