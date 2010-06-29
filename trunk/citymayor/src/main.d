import std.stdio;
import std.string;

import config.config;
import city.city;
import gui.gui;
import debuggui.debuggui;
import city.data;

void main()
{
	initializeStaticData();
	
	City city = new City(15, 15);
	GUI gui = new DebugGUI(city, 300, 300);
	gui.run();
}