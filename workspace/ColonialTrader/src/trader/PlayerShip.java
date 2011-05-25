package trader;

import java.util.HashMap;

public class PlayerShip extends Ship {

	/** Amount of goods stored on the ship. */
	public HashMap<Good, Integer> amount = new HashMap<Good, Integer>();
	
	/** Create a new ship (human controlled). */
	public PlayerShip(ShipClass shipClass)
	{
		this.shipClass = shipClass;
		for(Good good: Good.list)
			amount.put(good, 0);
	}

	/** Returns the range of the ship, that is, the distance it can travel. */
	public double getRange()
	{
		return shipClass.range;
	}
	
	/** Returns the amount of goods the ship can store. */
	public int getCapacity()
	{
		return shipClass.capacity;
	}

	/** Return the number of storage slots used. */
	public int getSpacesUsed()
	{
		int s = 0;
		for(Good good: Good.list)
			s += amount.get(good);
		return s;
	}
	
	/** Attack a ship */
	public void attack(Ship ship) {
		ship.integrity -= 50;
	}

	/** Returns the cost by travel (crew cost). */
	public int getCost() {
		// TODO Auto-generated method stub
		return 0;
	}
}
