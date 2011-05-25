package trader;

public abstract class Ship {
	
	/** Class of the ship. */
	public ShipClass shipClass;
	
	/** The "health" of the ship. */
	public int integrity = 100;
	
	protected Ship() { }

	/** Returns a number defining the strength of a ship. */
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

}
