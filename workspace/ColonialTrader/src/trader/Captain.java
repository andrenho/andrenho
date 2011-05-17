package trader;

public class Captain {

	public final String name;
	public final int pilot, fighter, trader, shipwright;
	public Ship ship;
	public World world;
	public City docked = null;
	
	public Captain(String name, int pilot, int fighter, int trader, int shipwright)
	{
		this.name = name;
		this.pilot = pilot;
		this.fighter = fighter;
		this.trader = trader;
		this.shipwright = shipwright;
		this.ship = new Ship(ShipClass.CARAVEL);
		
		assert (pilot + fighter + trader + shipwright) == 20;
	}
	
}
