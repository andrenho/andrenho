import std.stdio;
import std.string;

import config.config;

//alias string[string] ConfigNode;
//alias ConfigNode[][string] Config;

void main()
{
	Config config = readConfigFile("etc/citymayor.cfg");
	//writefln(config["Commerce"][2]["Name"]);
	foreach(string key, ConfigNode[] cns; config)
	{
		writefln(format("--- %s (%d) ---", key, cns.length));
		foreach(ConfigNode cn; cns)
			writefln(cn["Identifier"]);
		writefln("");
	}
}