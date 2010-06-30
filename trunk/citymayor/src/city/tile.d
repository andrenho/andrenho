module city.tile;

import std.string, std.xml, std.conv;

import city.structure;

class Tile
{
	uint x, y;
	Structure structure;
	
	this(uint x, uint y)
	{
		this.x = x;
		this.y = y;
	}
	
	//
	// Serialization
	//
	
	string serialize()
	{
		return format("<tile x=\"%d\" y=\"%d\" />", x, y);
	}
	
	this(Element e)
	{
		x = to!uint(e.tag.attr["x"]);
		y = to!uint(e.tag.attr["y"]);
	}
}
