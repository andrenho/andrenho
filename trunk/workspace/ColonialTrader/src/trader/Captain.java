package trader;

import java.util.HashMap;
import java.util.Vector;

public class Captain {
	
	@SuppressWarnings("serial")
	public class NoMoneyLeftException extends Exception { }
	@SuppressWarnings("serial")
	public class NoSpaceLeftException extends Exception { }
	@SuppressWarnings("serial")
	public class NoGoodsInTownException extends Exception { }
	@SuppressWarnings("serial")
	public class NoGoodsInShipException extends Exception { }

	public final String name;
	public final int pilot, fighter, trader, shipwright;
	public Ship ship;
	public World world;
	private City docked = null;

	public int doubloons = 2000;
	protected static Captain captain = null;
	
	public HashMap<City, Integer> availableCities = new HashMap<City, Integer>();
	
	protected Captain(String name, int pilot, int fighter, int trader, int shipwright, World w)
	{
		this.name = name;
		this.pilot = pilot;
		this.fighter = fighter;
		this.trader = trader;
		this.shipwright = shipwright;
		this.ship = new Ship(ShipClass.CARAVEL);
		this.world = w;
		
		City initialCity = (world.cities.get((int) (Math.random() * world.n_cities)));
		this.docked = initialCity;
		updateAvailableCities();
		
		assert (pilot + fighter + trader + shipwright) == 20;
	}
	
	public static Captain create(String name, int pilot, int fighter, int trader, int shipwright, World w) throws Exception
	{
		if(captain != null)
			throw new Exception("Captiain already created.");
		captain = new Captain(name, pilot, fighter, trader, shipwright, w);
		return captain;
	}

	public static Captain getCaptain() {
		return captain;
	}

	public void buy(Good good, int i) 
			throws NoSpaceLeftException, NoMoneyLeftException, NoGoodsInTownException 
	{
		assert docked != null;
		assert ship != null;
		
		if(i > (ship.getCapacity() - ship.getSpacesUsed()))
			throw new NoSpaceLeftException();
		if(i * docked.getPriceBuy(good) > doubloons)
			throw new NoMoneyLeftException();
		if(i > docked.amount.get(good))
			throw new NoGoodsInTownException();
		
		ship.amount.put(good, ship.amount.get(good) + i);
		docked.amount.put(good, docked.amount.get(good) - i);
		doubloons -= i * docked.getPriceBuy(good);
		
		assert doubloons >= 0;
	}

	public void sell(Good good, int i) throws NoGoodsInShipException 
	{
		assert docked != null;
		assert ship != null;
		assert ship.amount.get(good) >= i;
		
		if(i > ship.amount.get(good))
			throw new NoGoodsInShipException();
		
		ship.amount.put(good, ship.amount.get(good) - i);
		docked.amount.put(good, docked.amount.get(good) + i);
		doubloons += i * docked.getPriceSell(good);
	}

	public void buyAll(Good good) 
	{
		assert docked != null;
		assert ship != null;
		
		int i = doubloons / docked.getPriceBuy(good);
		if(i > ship.getCapacity() - ship.getSpacesUsed())
			i = ship.getCapacity() - ship.getSpacesUsed();
		if(i > docked.amount.get(good))
			i = docked.amount.get(good);
		
		try {
			buy(good, i);
		} catch (Exception e) {
			e.printStackTrace();
			assert false;
		}
	}

	public void sellAll(Good good) 
	{
		assert good != null;
		
		int i = ship.amount.get(good);
		try {
			sell(good, i);
		} catch (NoGoodsInShipException e) {
			e.printStackTrace();
			assert false;
		}
	}

	public void travel(City city) 
	{
		Travel travel = new Travel(city);
		while(!travel.areWeThereYet())
			travel.encounter();
		this.docked = city;
		updateAvailableCities();
		doubloons -= ship.getCost();
		if(doubloons < 0)
			// TODO - reduce morale
			doubloons = 0;
	}

	private void updateAvailableCities() {
		availableCities.clear();
		for(City city2: world.cities)
			if(this.docked != city2)
			{
				if(world.estimateCost(this.docked.coordinates, city2.coordinates) < ShipClass.maxRange)
				{
					Vector<Coordinate> c = world.pathBetweenCoordinates(this.docked.coordinates, city2.coordinates);
					if(c != null)
						availableCities.put(city2, c.size());
				}
			}
	}

	public City getDocked() {
		return docked;
	}
}
