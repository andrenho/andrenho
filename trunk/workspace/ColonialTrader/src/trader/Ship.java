package trader;

public class Ship {
	
	public final ShipClass shipClass;

	public Ship(ShipClass shipClass)
	{
		this.shipClass = shipClass;
	}
	
	public double getRange()
	{
		return shipClass.range;
	}

}
