package trader;

import java.util.HashMap;

public class Ship {
	
	public final ShipClass shipClass;
	public HashMap<Good, Integer> amount = new HashMap<Good, Integer>();

	public Ship(ShipClass shipClass)
	{
		this.shipClass = shipClass;
		for(Good good: Good.list)
			amount.put(good, 0);
	}
	
	public double getRange()
	{
		return shipClass.range;
	}
	
	public int getCapacity()
	{
		return shipClass.capacity;
	}

	public int getSpacesUsed()
	{
		int s = 0;
		for(Good good: Good.list)
			s += amount.get(good);
		return s;
	}
}
