package trader;

public class Good {

	public final String name;
	public final boolean legal;
	public final int basicValue;
	
	public Good(String name, boolean legal, int basicValue)
	{
		this.name = name;
		this.legal = legal;
		this.basicValue = basicValue;
	}
	
	public final static Good FOOD = new Good("Food", true, 5);
	public final static Good WOOD = new Good("Wood", true, 6);
	public final static	Good FURS = new Good("Furs", true, 7);
	public final static	Good ORE = new Good("Ore", true, 16);
	public final static	Good GOLD = new Good("Gold", true, 30);
	public final static	Good MEDICINE = new Good("Medicine", true, 40);
	public final static	Good BOOKS = new Good("Books", true, 25);
	public final static	Good OPIUM = new Good("Opium", false, 90);
	public final static	Good MUSKETS = new Good("Muskets", false, 60);

	public final static Good[] list = { FOOD, WOOD, FURS, ORE, GOLD, MEDICINE, BOOKS, OPIUM, MUSKETS };
}
