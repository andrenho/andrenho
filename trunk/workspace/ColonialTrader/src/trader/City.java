package trader;

import java.util.Arrays;
import java.util.Collections;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Random;
import java.util.Set;

public class City {

	public enum Type { AGRICULTURAL, PROSPECTING, INDUSTRIAL, URBAN, ARISTOCRATIC };
	public enum Terrain { PLAINS, DESERT, ARCTIC, MOUNTAINS, FOREST };

	protected HashMap<Good, Integer> price;
	private static Set<String> namesUsed = new HashSet<String>();

	public final String name;
	public final Coordinate coordinates;
	public final Bar bar;
	public ShipMerchant shipMerchant = null;
	public Drydock drydock = null;
	public final Terrain terrain;
	public Type type;
	public HashMap<Good, Integer> amount;
	
	protected City(String name, Coordinate coordinates, Terrain terrain, Type type)
	{
		this.name = name;
		this.coordinates = coordinates;
		this.terrain = terrain;
		this.type = type;
		
		this.bar = new Bar();
		if(type == Type.INDUSTRIAL || type == Type.URBAN || type == Type.ARISTOCRATIC)
		{
			this.shipMerchant = new ShipMerchant();
			this.drydock = new Drydock();
		}
		
		createWarehouse();
		for(int i=0; i<20; i++)
			produceAndUpdatePrices();
	}
	
	protected static Terrain chooseTerrain(Coordinate coordinates)
	{
		double height = coordinates.y / (double)World.h;
		System.out.println(height);
		Terrain terrain;
		if(height < 0.2 || height > 0.8)
			terrain = (Math.random() < 0.5 ? Terrain.ARCTIC : Terrain.MOUNTAINS);
		else if(height < 0.4 || height > 0.6)
			terrain = (Math.random() < 0.5 ? Terrain.PLAINS : Terrain.FOREST);
		else
			terrain = (Math.random() < 0.5 ? Terrain.PLAINS : Terrain.DESERT);
		return terrain;
	}

	public City(Coordinate coordinates) {
		this(nameAutoGen(), coordinates,
				chooseTerrain(coordinates),
				Collections.unmodifiableList(Arrays.asList(Type.values())).get((new Random()).nextInt(Type.values().length)));
	}

	private static String nameAutoGen() {
		String[] spanishPrefixF = { "Nueva", "Santa", "De la", "La", "Sierra", "Buena", "Monte" },
		         spanishPrefixM = { "Nuevo", "San", "El", "Del", "Boca", "Bueno", "Monte" },
		         spanishF = { "Alameda", "Angelina", "Atascosa", "Bandera", "Calavera", "Fe",
							  "Esmeralda", "Paz", "Plata", "Madera", "Barbara", "Clara",
							  "Cruz", "Bonita", "Espa�ola", "Vista", "Mesa", "Quinta", 
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

	private void createWarehouse() 
	{
		amount = new HashMap<Good, Integer>();
		for(Good good: Good.list)
			amount.put(good, 10);

		price = new HashMap<Good, Integer>();
		for(Good good: Good.list)
			price.put(good, 5);
	}
	
	public Integer getPriceBuy(Good good)
	{
		int pr = (int)(price.get(good) * 1.1);
		if(pr == price.get(good))
			return pr + 1;
		else
			return pr;
	}

	public Integer getPriceSell(Good good) {
		return price.get(good);
	}

	private void produceAndUpdatePrices() {
	}
}
