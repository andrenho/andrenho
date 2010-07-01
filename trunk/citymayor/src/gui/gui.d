module gui.gui;

import city.city;
import std.stdio, std.string;
import std.xml;

abstract class GUI
{
	City city;
	
	this(City city)
	{
		this.city = city;
	}
	
	
	void run();
	
	
	void displayException(Exception e)
	{
		throw e;
	}
	
	
	void saveCity(string file)
	{
		auto f = File(file, "w");
		string s = city.serialize();
		auto xml = new Document(s);
		f.write(xml);
		writefln(format("File %s saved.\n", file));
	}
	
	
	void loadCity(string file)
	{
		auto s = cast(string)std.file.read(file);
		check(s);		
		auto xml = new Document(s);
		city = new City(xml);
		writefln(format("File %s loaded.\n", file));
	}
}