import std.stdio;
import std.string;

import config.config;
import city.city;
import gui.gui;
import debuggui.debuggui;

void main()
{
	City city = new City(15, 15);
	GUI gui = new DebugGUI(city);
	gui.run();
}