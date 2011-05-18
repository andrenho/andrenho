package trader;

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
	public City docked = null;
	public int doubloons = 2000;
	protected static Captain captain = null;
	
	protected Captain(String name, int pilot, int fighter, int trader, int shipwright)
	{
		this.name = name;
		this.pilot = pilot;
		this.fighter = fighter;
		this.trader = trader;
		this.shipwright = shipwright;
		this.ship = new Ship(ShipClass.CARAVEL);
		
		assert (pilot + fighter + trader + shipwright) == 20;
	}
	
	public static Captain create(String name, int pilot, int fighter, int trader, int shipwright) throws Exception
	{
		if(captain != null)
			throw new Exception("Captiain already created.");
		captain = new Captain(name, pilot, fighter, trader, shipwright);
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
		if(i * docked.priceBuy(good) > doubloons)
			throw new NoMoneyLeftException();
		if(i > docked.amount.get(good))
			throw new NoGoodsInTownException();
		
		ship.amount.put(good, ship.amount.get(good) + i);
		docked.amount.put(good, docked.amount.get(good) - i);
		doubloons -= i * docked.priceBuy(good);
		docked.updatePrices();
		
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
		doubloons += i * docked.priceSell(good);

		docked.updatePrices();
	}

	public void buyAll(Good good) 
	{
		assert docked != null;
		assert ship != null;
		
		int i = doubloons / docked.priceBuy(good);
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

	public void travel(City city) {
		// TODO - a lot!
		this.docked = city;
	}
}
