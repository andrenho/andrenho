module city.road;

import std.stdio, std.string, std.conv, std.xml;

import city.city;
import city.structure;

class RoadData : StructureData
{
	uint maxSpeed;

	this(string identifier, string name, uint w, uint h, uint price, uint maxSpeed)
	{
		super(identifier, name, w, h, price);
		this.maxSpeed = maxSpeed;
	}
}


class Road : Structure
{
	static RoadData[string] data;

	this(StructureData dt)
	{
		super(dt);
	}
	
	//
	// Serialization
	//
	
	override string serialize() 
	{
		return format("<road x=\"%d\" y=\"%d\" id=\"%s\" />", tile.x, tile.y, dt.identifier);
	}
	
	this(Element e)
	{
		assert(e.tag.name == "road");
		dt = cast(RoadData)data[e.tag.attr["id"]];
	}
}
