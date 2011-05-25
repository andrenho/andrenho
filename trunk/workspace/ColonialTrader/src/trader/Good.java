package trader;
 
public class Good {

	/** Good name. */
	public final String name;
	
	/** True if it's legal to buy and sell this good. */
	public final boolean legal;
	
	/** The basic value of the city, not adjusted by supply and demand. */
	public final int basicValue;
	
	public Good(String name, boolean legal, int basicValue)
	{
		this.name = name;
		this.legal = legal;
		this.basicValue = basicValue;
	}
	
	public final static Good FOOD = new Good("Food", true, 10);
	public final static Good WOOD = new Good("Wood", true, 15);
	public final static	Good FURS = new Good("Furs", true, 20);
	public final static	Good ORE = new Good("Ore", true, 150);
	public final static	Good GOLD = new Good("Gold", true, 300);
	public final static	Good MEDICINE = new Good("Medicine", true, 200);
	public final static	Good BOOKS = new Good("Books", true, 60);
	public final static	Good OPIUM = new Good("Opium", false, 700);
	public final static	Good MUSKETS = new Good("Muskets", false, 400);
	public final static	Good RUM = new Good("Rum", false, 300);

	public final static Good[] list = { FOOD, WOOD, FURS, ORE, GOLD, MEDICINE, BOOKS, OPIUM, MUSKETS, RUM };
}
