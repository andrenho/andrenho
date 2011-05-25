package trader; 

import java.util.HashMap;
import java.util.Vector;

public class Captain {
	
	//
	// exceptions caused by buy/sell
	//
	@SuppressWarnings("serial")
	public class NoMoneyLeftException extends Exception { }
	@SuppressWarnings("serial")
	public class NoSpaceLeftException extends Exception { }
	@SuppressWarnings("serial")
	public class NoGoodsInTownException extends Exception { }
	@SuppressWarnings("serial")
	public class NoGoodsInShipException extends Exception { }

	/** Captain name */
	public final String name;
	
	/** Captian skills */
	public final int pilot, fighter, trader, shipwright;
	
	/** Ship the captain is using. */
	public PlayerShip ship;
	
	/** World the captain is living into. */
	public World world;
	
	/** City where the captain's ship is currently docked. */
	private City docked = null;

	/** Money the captain carries with him. */
	public int doubloons = 2000;
	
	/** Self-reference. */
	protected static Captain captain = null;
	
	/** Cities into the range of the captain ship. Is recalculated every time
	 *  the captain travels somewhere. */
	public HashMap<City, Integer> availableCities = new HashMap<City, Integer>();
	
	/** Create a new captain. */
	protected Captain(String name, int pilot, int fighter, int trader, int shipwright, World w)
	{
		this.name = name;
		this.pilot = pilot;
		this.fighter = fighter;
		this.trader = trader;
		this.shipwright = shipwright;
		this.ship = new PlayerShip(ShipClass.CARAVEL);
		this.world = w;
		
		City initialCity = (world.cities.get((int) (Math.random() * world.n_cities)));
		this.docked = initialCity;
		updateAvailableCities();
		
		assert (pilot + fighter + trader + shipwright) == 20;
	}
	
	/** Create a new captain (singleton method). */
	public static Captain create(String name, int pilot, int fighter, int trader, int shipwright, World w) throws Exception
	{
		if(captain != null)
			throw new Exception("Captiain already created.");
		captain = new Captain(name, pilot, fighter, trader, shipwright, w);
		return captain;
	}

	/** Returns the current game captain. */
	public static Captain getCaptain() {
		return captain;
	}

	/** Return the port where the captain ship is docked. */
	public City getDocked() {
		return docked;
	}

	/** Buy a certain amount of goods. */
	public void buy(Good good, int i) 
			throws NoSpaceLeftException, NoMoneyLeftException, NoGoodsInTownException 
	{
		assert docked != null;
		assert ship != null;
		
		if(i > (ship.getCapacity() - ship.getSpacesUsed()))
			throw new NoSpaceLeftException();
		if(i * docked.getBuyingPrice(good) > doubloons)
			throw new NoMoneyLeftException();
		if(i > docked.amount.get(good))
			throw new NoGoodsInTownException();
		
		ship.amount.put(good, ship.amount.get(good) + i);
		docked.amount.put(good, docked.amount.get(good) - i);
		doubloons -= i * docked.getBuyingPrice(good);
		
		assert doubloons >= 0;
	}

	/** Sell a certain amount of goods. */
	public void sell(Good good, int i) throws NoGoodsInShipException 
	{
		assert docked != null;
		assert ship != null;
		assert ship.amount.get(good) >= i;
		
		if(i > ship.amount.get(good))
			throw new NoGoodsInShipException();
		
		ship.amount.put(good, ship.amount.get(good) - i);
		docked.amount.put(good, docked.amount.get(good) + i);
		doubloons += i * docked.getSellingPrice(good);
	}

	/** Buy as much as possible of a given good. */
	public void buyAll(Good good) 
	{
		assert docked != null;
		assert ship != null;
		
		int i = doubloons / docked.getBuyingPrice(good);
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

	/** Sell as much as possible of a given good. */
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

	/** Travel to a new city. */
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

	/** Update the list of reachable cities. */
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

}
