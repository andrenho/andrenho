package trader;

import java.util.Arrays;
import java.util.Collections;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Random;
import java.util.Set;

public class City {

	public enum Terrain { PLAINS, DESERT, ARCTIC, MOUNTAINS, FOREST };
	public enum Type { AGRICULTURAL, PROSPECTING, INDUSTRIAL, URBAN, ARISTOCRATIC, PIRATE };

	/** Buying price of the goods of the city. */
	protected HashMap<Good, Integer> sellingPrice;
	
	/** List of city names already used, to avoid repetition. */
	private static Set<String> namesUsed = new HashSet<String>();
	
	/** City name. */
	public final String name;
	
	/** City coordinates. */
	public final Coordinate coordinates;

/*
	public final Bar bar;
	public ShipMerchant shipMerchant = null;
	public Drydock drydock = null;
*/
	public final Terrain terrain;
	public Type type;
	
	/** Amount of goods available for sale in the city. */
	public HashMap<Good, Integer> amount;
	
	/** How much the residents of a city want of a given good? Used to calculate prices. */
	public HashMap<Good, Integer> want = new HashMap<Good, Integer>();
	
	/** How much the city produces of that given good. */
	public HashMap<Good, Integer> production = new HashMap<Good, Integer>();

	/** Define the kind of terrain of the city. */
	protected static Terrain chooseTerrain(Coordinate coordinates)
	{
		double height = coordinates.y / (double)World.h;
		Terrain terrain;
		if(height < 0.2 || height > 0.8)
			terrain = (Math.random() < 0.5 ? Terrain.ARCTIC : Terrain.MOUNTAINS);
		else if(height < 0.4 || height > 0.6)
			terrain = (Math.random() < 0.5 ? Terrain.PLAINS : Terrain.FOREST);
		else
			terrain = (Math.random() < 0.5 ? Terrain.PLAINS : Terrain.DESERT);
		return terrain;
	}
	
	
	/** Generate random colonial city names. */
	private static String nameAutoGen() 
	{
		String[] spanishPrefixF = { "Nueva", "Santa", "De la", "La", "Sierra", "Buena", "Monte" },
		         spanishPrefixM = { "Nuevo", "San", "El", "Del", "Boca", "Bueno", "Monte" },
		         spanishF = { "Alameda", "Angelina", "Atascosa", "Bandera", "Calavera", "Fe",
							  "Esmeralda", "Paz", "Plata", "Madera", "Barbara", "Clara",
							  "Cruz", "Bonita", "Española", "Vista", "Mesa", "Quinta", 
							  "Muerte" },
				 spanishM = { "Amador", "Conejo", "Soto", "Norte", "Dorado", "Hernando",
		        		      "Monterey", "Sacramento", "Benito", "Diego", "Franscisco",
		        		      "Juan", "Patricio", "Chico", "Paso", "Gordo", "Indio", 
		        		      "Gato", "Palacio", "Pueblo", "Antonio", "Marcos", 
		        		      "Vallejo", "Paraiso" },
		         englishPrefix = { "New", "Saint", "South", "North", "East", "West" },
		         englishPostfix = { "Hill", "River", "Mountain", "Falls", "City", "Valley", "Lake", "Creek", "Junction" },
		         english = { "Ackley", "Albert", "Andover", "Arlington", "Aurora", "Bancroft",
				             "Barnes", "Baxter", "Berkley", "Brooklyn", "Buffalo", "Carlisle",
				             "Carson", "Cedar", "Central", "Clear", "Columbus", "Conway", "Dakota",
				             "Sioux", "Davenport", "Dawson", "Eldora", "Emerson", "Fairbank",
				             "Forest City", "Franklin", "Gilmore", "Halbur", "Hull", "Jackson",
				             "Keosauqua", "Lenox", "McIntire", "Marble", "Missouri", "Sun", "Union",
				             "Nevada", "Providence", "Oakland", "Pacific", "Plainfield", "Radcliffe",
				             "Rose", "Sheffield", "Spring", "Hope", "Titonka", "Volga", "Walker",
				             "Washington", "Webster", "Wyoming", "York" };
		
		String name;
		char type;
		if(Math.random() > 0.5)
		{
			do
			{
				if(Math.random() > 0.5)
				{
					name = spanishF[(int) (Math.random() * spanishF.length)];
					type = 'F';
				}
				else
				{
					name = spanishM[(int) (Math.random() * spanishM.length)];
					type = 'M';
				}
			} while(namesUsed.contains(name));
			namesUsed.add(name);
			
			if(Math.random() > 0.5)
			{
				if(type == 'F')
					return spanishPrefixF[(int) (Math.random() * spanishPrefixF.length)] + " " + name;
				else
					return spanishPrefixM[(int) (Math.random() * spanishPrefixM.length)] + " " + name;
			}
			else
				return name;
		}
		else			
		{
			do
			{
				name = english[(int) (Math.random() * english.length)];
			} while(namesUsed.contains(name));
			namesUsed.add(name);

			if(Math.random() > 0.6)
				return name;
			else if(Math.random() > 0.3)
				return name + " " + englishPostfix[(int) (Math.random() * englishPostfix.length)];
			else
				return englishPrefix[(int) (Math.random() * englishPrefix.length)] + " " + name;
		}
	}

	/** Create a new city. */
	City(Coordinate coordinates) {
		this(nameAutoGen(), coordinates,
				chooseTerrain(coordinates),
				Collections.unmodifiableList(Arrays.asList(Type.values())).get((new Random()).nextInt(Type.values().length)));
	}

	/** Create a new city. */
	protected City(String name, Coordinate coordinates, Terrain terrain, Type type)
	{
		this.name = name;
		this.coordinates = coordinates;
		this.terrain = terrain;
		this.type = type;
		
		//this.bar = new Bar();
		if(type == Type.INDUSTRIAL || type == Type.URBAN || type == Type.ARISTOCRATIC || type == Type.PIRATE)
		{
			//this.shipMerchant = new ShipMerchant();
			//this.drydock = new Drydock();
		}

		setupNeedandProduction();
		createWarehouse();
		for(int i=0; i<20; i++)
			produceAndUpdatePrices();
	}

	/** Create the city's warehouse. */
	private void createWarehouse() 
	{
		amount = new HashMap<Good, Integer>();
		for(Good good: Good.list)
			amount.put(good, 10);

		sellingPrice = new HashMap<Good, Integer>();
		for(Good good: Good.list)
			sellingPrice.put(good, 5);
	}

	/** Return the buying price of a given good. */
	public Integer getBuyingPrice(Good good)
	{
		int pr = (int)(sellingPrice.get(good) * 1.1);
		if(pr == sellingPrice.get(good))
			return pr + 1;
		else
			return pr;
	}

	/** Return the selling price of a given good. */
	public Integer getSellingPrice(Good good) 
	{
		return sellingPrice.get(good);
	}

	/** Update the amount of goods available in the city. Runs every time the captain travels. */
	private void produceAndUpdatePrices() 
	{
		for(Good good: Good.list)
		{
			int q = amount.get(good);
			q += production.get(good) + (int)(Math.random() * 11 - 3);
			q -= want.get(good) + (int)(Math.random() * 11 - 5);
			if(q >= 0)
				amount.put(good, q);
			else
				amount.put(good, 0);
			adjustPrice(good);
		}
	}
	
	/** Recalculate the prices based on supply & demand. */
	private void adjustPrice(Good good) {
		sellingPrice.put(good, (int)(good.basicValue * ((want.get(good)+50) / (double)(amount.get(good)+50)))); 
	}

	/** Returns a random integer between -1 and 1. */
	private int unaryRandom() {
		return (int)(Math.random() * 3 - 1);
	}

	/** Helper function to adjust production.  */
	private void setGood(HashMap<Good, Integer> type, Good good, int plains, int desert,	
			int arctic,	int mountains, int forest, int agricultural, int prospecting, 
			int industrial, int urban, int aristocractic, int pirate) 
	{
		int t1=0, t2=0;
		switch(this.type)
		{
			case AGRICULTURAL: t1 = agricultural + unaryRandom(); break;
			case PROSPECTING: t1 = prospecting + unaryRandom(); break;
			case INDUSTRIAL: t1 = industrial + unaryRandom(); break;
			case URBAN: t1 = urban + unaryRandom(); break;
			case ARISTOCRATIC: t1 = aristocractic + unaryRandom(); break;
			case PIRATE: t1 = pirate + unaryRandom(); break;
			default: assert false;
		}
		switch(this.terrain)
		{
			case PLAINS: t2 = plains + unaryRandom(); break;
			case DESERT: t2 = desert + unaryRandom(); break;
			case ARCTIC: t2 = arctic + unaryRandom(); break;
			case MOUNTAINS: t2 = mountains + unaryRandom(); break;
			case FOREST: t2 = forest + unaryRandom(); break;
			default: assert false;
		}
		type.put(good, t1+t2);
	}

	/** Setup production and necessities of the city. */
	private void setupNeedandProduction() {
		setGood(want, Good.FOOD,    -2,  4, 3,  3,  1, -2,  3, 2, 3, 4,  1);
		setGood(want, Good.WOOD,    -1,  3, 0, -2, -2,  2,  2, 4, 3, 1,  1);
		setGood(want, Good.FURS,     0, -2, 5,  3, -1,  0,  0, 1, 2, 3,  0);
		setGood(want, Good.ORE,      2, -2, 1, -2,  2,  3,  2, 5, 3, 0, -1);
		setGood(want, Good.GOLD,     1, -2, 1, -3,  2,  0, -2, 2, 4, 7,  3);
		setGood(want, Good.MEDICINE, 2,  3, 4,  2,  1,  4,  3, 2, 3, 4,  2);
		setGood(want, Good.BOOKS,    1,  2, 4,  3,  2,  0,  0, 1, 3, 5,  0);
		setGood(want, Good.RUM,      0,  0, 2,  1,  0, -2,  3, 2, 1, 2,  7);
		setGood(want, Good.OPIUM,    3,  4, 3,  3,  2,  2,  4, 3, 3, 5,  2);
		setGood(want, Good.MUSKETS,  1,  3, 2,  3,  3,  0,  3, 4, 3, 2,  6);

		setGood(production, Good.FOOD,     5, 0, 0, 1, 2, 5, 0, 0, 0, 0, 0);
		setGood(production, Good.WOOD,     2, 0, 1, 3, 5, 2, 0, 1, 1, 1, 0);
		setGood(production, Good.FURS,     1, 0, 1, 2, 4, 0, 0, 1, 0, 0, 0);
		setGood(production, Good.ORE,      0, 3, 2, 5, 0, 0, 5, 1, 0, 0, 0);
		setGood(production, Good.GOLD,     0, 2, 1, 3, 0, 0, 3, 2, 0, 0, 3);
		setGood(production, Good.MEDICINE, 0, 0, 0, 0, 0, 0, 0, 1, 3, 5, 0);
		setGood(production, Good.BOOKS,    2, 0, 0, 0, 1, 1, 0, 1, 2, 3, 0);
		setGood(production, Good.RUM,      3, 0, 0, 0, 1, 2, 0, 3, 1, 1, 2);
		setGood(production, Good.OPIUM,    3, 0, 0, 0, 1, 3, 0, 0, 0, 0, 4);
		setGood(production, Good.MUSKETS,  0, 0, 0, 1, 0, 0, 1, 4, 3, 2, 4);
	}
}
