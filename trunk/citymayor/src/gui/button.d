module gui.button;

import derelict.sdl.sdl;

import std.xml;

import gui.defaultgui;

class Button
{
	static DefaultGUI gui;
	
	SDL_Surface* image;
	string type;
	
	this(Element e)
	{
		assert(e.tag.name == "button");
		type = e.tag.attr["type"];
		image = gui.loadImage(e.tag.attr["image"]);
	}
}