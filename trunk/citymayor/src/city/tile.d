module city.tile;

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
}
