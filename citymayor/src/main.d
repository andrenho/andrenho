import std.stdio;
import std.string;
import std.getopt;

import config.config;
import city.city;
import gui.gui;
import gui.defaultgui;
import debuggui.debuggui;
import city.data;


void main(string[] args)
{
	bool debug_gui;
	getopt(args, "debuggui", &debug_gui);
	
	initializeStaticData();
	
	City city = new City(15, 15);
	
	GUI gui;
	if(debug_gui)
		gui = new DebugGUI(city, 300, 300);
	else
		gui = new DefaultGUI(city);
		
	try
	{
		gui.run();
	}
	catch(Exception e)
	{
		gui.displayException(e);
	}
}