package trader;

public class ShipClass {

	public String name;
	public final double range;

	protected ShipClass(String name, double range)
	{
		this.name = name;
		this.range = range;
	}
	
	public static ShipClass CARAVEL = new ShipClass("Caravel", 100.0); 
}
