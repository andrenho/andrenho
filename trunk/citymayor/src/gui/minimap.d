module gui.minimap;

import derelict.sdl.sdl;

import city.city;

class MiniMap
{
	const uint w = 140;
	const uint h = 100;
	
	private
	{
		City city;
	}
	
	this(City city)
	{
		this.city = city;
	}
}