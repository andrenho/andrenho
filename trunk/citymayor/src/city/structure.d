module city.structure;

import city.tile;

abstract class StructureData
{
	string name;
	uint w, h;
	uint price;
	
	this(string name, uint w, uint h, uint price)
	{
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
	}
}
