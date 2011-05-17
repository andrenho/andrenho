package trader;

public class Good {

	public String name;
	public boolean legal;
	
	public Good(String name, boolean legal)
	{
		this.name = name;
		this.legal = legal;
	}
	
	public final static Good[] list = {
		new Good("Food", true),
	};
}
