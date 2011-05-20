package trader;

public class ShipClass {

	public String name;
	public final double range;
	public final int capacity;
	public final int price;
	public final static int maxRange = 25;

	protected ShipClass(String name, double range, int capacity, int price)
	{
		this.name = name;
		this.range = range;
		this.capacity = capacity;
		this.price = price;
	}
	
	public static ShipClass CARAVEL     = new ShipClass("Caravel",     100.0,  20,  10000);
	public static ShipClass MARCHANTMAN = new ShipClass("Merchantman", 110.0,  50,  30000);
	public static ShipClass GALEON      = new ShipClass("Galeon",       80.0, 130,  70000);
	public static ShipClass PRIVATEER   = new ShipClass("Privateer",   140.0,  40,  70000);
	public static ShipClass FRIGATE     = new ShipClass("Frigate",     110.0,  70, 180000);
	public static ShipClass MAN_O_WAR   = new ShipClass("Man-O-War",   100.0,  90, 400000);
}
