module city.data;

import std.stdio, std.string, std.conv;

import config.config;
import city.road;

void initializeStaticData()
{
	uint w(string s)
	{
		return to!uint(s.split("x")[0]);
	}
	
	uint h(string s)
	{
		return to!uint(s.split("x")[1]);
	}
	
	
	Config config = readConfigFile("./etc/citymayor.cfg");
	
	// load roads
	foreach(ConfigNode cn; config["Roads"])
		Road.data[cn["Identifier"]] = new RoadData(cn["Identifier"],
													cn["Name"], 
													w(cn["Size"]),
													h(cn["Size"]),
													to!uint(cn["Price"]), 
													to!uint(cn["MaxSpeed"]));
}