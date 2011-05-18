package trader;

public class ShipClass {

	public String name;
	public final double range;
	public final int capacity;

	protected ShipClass(String name, double range, int capacity)
	{
		this.name = name;
		this.range = range;
		this.capacity = capacity;
	}
	
	public static ShipClass CARAVEL = new ShipClass("Caravel", 100.0, 20); 
}
