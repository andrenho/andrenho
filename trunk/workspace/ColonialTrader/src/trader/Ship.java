package trader;

import java.util.HashMap;

public class Ship {
	
	public ShipClass shipClass;
	public HashMap<Good, Integer> amount = new HashMap<Good, Integer>();
	public final CaptainType captainType;
	public enum CaptainType { PLAYER, PIRATE, MERCHANT, GOVERNMENT };
	public int integrity = 100;

	public Ship(ShipClass shipClass)
	{
		this.shipClass = shipClass;
		this.captainType = CaptainType.PLAYER;
		for(Good good: Good.list)
			amount.put(good, 0);
	}
	
	public Ship(CaptainType captainType)
	{
		this.captainType = captainType;
		for(Good good: Good.list)
			amount.put(good, 0);
		autoGenerate();
		assert shipClass != null;
	}
	
	private void autoGenerate() 
	{
		assert captainType != CaptainType.PLAYER;
		double enemyStrength = Captain.getCaptain().ship.overallStrength() + Math.random() / 2 - 0.3; // TODO - dificulty
		if(enemyStrength < 1/6)
			this.shipClass = ShipClass.CARAVEL;
		else if(enemyStrength < 2/6)
			this.shipClass = ShipClass.MARCHANTMAN;
		else if(enemyStrength < 3/6)
			this.shipClass = ShipClass.GALEON;
		else if(enemyStrength < 4/6)
			this.shipClass = ShipClass.PRIVATEER;
		else if(enemyStrength < 5/6)
			this.shipClass = ShipClass.FRIGATE;
		else
			this.shipClass = ShipClass.MAN_O_WAR;
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
	
	public double overallStrength()
	{
		double str = 0.0;
		if(this.shipClass.equals(ShipClass.CARAVEL))
			str += 0.0;
		else if(this.shipClass.equals(ShipClass.MARCHANTMAN))
			str += 0.1;
		else if(this.shipClass.equals(ShipClass.GALEON))
			str += 0.2;
		else if(this.shipClass.equals(ShipClass.PRIVATEER))
			str += 0.5;
		else if(this.shipClass.equals(ShipClass.FRIGATE))
			str += 0.5;
		else if(this.shipClass.equals(ShipClass.MAN_O_WAR))
			str += 0.7;
		else
			assert false;
		// TODO - weapons
		return str;
	}

	public void attack(Ship ship) {
		ship.integrity -= 50;
	}

	public int getCost() {
		// TODO Auto-generated method stub
		return 0;
	}
}
