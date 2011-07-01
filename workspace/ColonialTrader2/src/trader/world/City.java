package trader.world;

import java.util.HashMap;
import java.util.Vector;
import trader.city.Bank;
import trader.city.Bar;
import trader.city.Shipyard;
import trader.city.Warehouse;

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
    
    
    /** Return the number of pirates, government and merchants to be found along the way. */
    public int[] numberOfEnemies()
    {
        return new int[]{ 3, 2, 1 };
    }
}
