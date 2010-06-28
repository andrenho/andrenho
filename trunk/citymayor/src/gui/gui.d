module gui.gui;

import city.city;

abstract class GUI
{
	City city;
	
	this(City city)
	{
		this.city = city;
	}
	
	void run();
}