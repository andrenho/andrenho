module city.structure;

public import std.conv, std.xml;

public import city.city;
import city.tile;

abstract class StructureData
{
	string identifier;
	string name;
	uint w, h;
	uint price;
	
	this(string identifier, string name, uint w, uint h, uint price)
	{
		this.identifier = identifier;
		this.name = name;
		this.w = w;
		this.h = h;
		this.price = price;
	}
}

abstract class Structure
{
	static StructureData[string] data;
	
	Tile tile;
	StructureData dt;
	
	this(StructureData dt) {
		this.dt = dt;
		assert(dt !is null);
	}
	
	protected this() { }
	
	abstract string serialize();
}
