package trader;

import java.util.Vector;

public class World {

	public final Vector<City> cities;
	
	public World()
	{
		cities = new Vector<City>();
		cities.add(new City("Testtown", new Coordinate(50.0, 50.0)));
	}
	
}
