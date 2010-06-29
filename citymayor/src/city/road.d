module city.road;

import city.structure;
import city.transportationstructure;

class RoadData : StructureData
{
	uint maxSpeed;

	this(string name, uint w, uint h, uint price, uint maxSpeed)
	{
		super(name, w, h, price);
		this.maxSpeed = maxSpeed;
	}
}


class Road : TransportationStructure
{
	static RoadData[string] data;
	
	RoadData dt;
	
	this(RoadData dt)
	{
		super(dt);
	}
}
