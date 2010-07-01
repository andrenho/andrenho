module gui.cityview;

import derelict.sdl.sdl;

import city.city;

class CityView
{
	alias sf this;
	
	private
	{
		City city;
		SDL_Surface* sf;
	}
	
	this(City city)
	{
		this.city = city;
	}
}