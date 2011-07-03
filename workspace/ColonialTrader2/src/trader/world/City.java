package trader.world;

import java.util.HashMap;
import java.util.Vector;

import trader.city.Bank;
import trader.city.Bar;
import trader.city.Shipyard;
import trader.city.Warehouse;
import trader.ship.EnemyShip.Type;

public class City
{
    public final String name;
    public final Coordinate coord;
    
    public final Bank bank;
    public final Bar bar = new Bar();
    public final Warehouse warehouse = new Warehouse();
    public final Shipyard shipyard = new Shipyard();
    
    public City(Coordinate coord)
    {
        this.name = CityNames.autoGenerate();
        this.coord = coord;
        
        this.bank = null;
    }
    
    
    /** Return a list of reacheable cities. */
    public HashMap<City, Integer> citiesInRange(World world, double maxRange) 
    {
        HashMap<City, Integer> cities = new HashMap<City, Integer>();
        for(City city: world.cities)
            if(world.estimateCost(this.coord, city.coord) < maxRange)
            {
                Vector<Coordinate> c = world.pathBetweenCoordinates(this.coord, city.coord);
                if(c != null)
                    cities.put(city, c.size());
            }
        return cities;
    }
    
    
    /** Return the density of pirates, government and merchants to be found along the way. */
	public double[] enemyDensity() {
		// TODO Auto-generated method stub
		return new double[] { 0.2, 0.3, 0.1 };
	}


	/** Return the level of the enemy, depending on the type of the city. */
	public double getLevel(Type type) {
		// TODO Auto-generated method stub
		return 0;
	}
}
