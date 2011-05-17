package trader;

public class City {

	public enum PoliticalSystem { ANARCHY, REBEL, COLONY, DICTATORSHIP, INDEPENDENT };
	public enum Type { AGRICULTURAL, PROSPECTING, INDUSTRIAL, URBAN, ARISTOCRATIC };

	public final String name;
	public final Coordinate coordinates;
	public final Bar bar;
	public final Warehouse warehouse;
	public ShipMerchant shipMerchant = null;
	public Drydock drydock = null;
	public PoliticalSystem politicalSystem;
	public Type type;
	
	public City(String name, Coordinate coordinates, PoliticalSystem politicalSystem,
			Type type)
	{
		this.name = name;
		this.coordinates = coordinates;
		this.politicalSystem = politicalSystem;
		this.type = type;
		
		this.bar = new Bar();
		this.warehouse = new Warehouse();
		if(type == Type.INDUSTRIAL || type == Type.URBAN || type == Type.ARISTOCRATIC)
		{
			this.shipMerchant = new ShipMerchant();
			this.drydock = new Drydock();
		}
	}
	
}
