package upinterfaces;

import java.io.InputStream;

public abstract class UPXML {
	
	public static UPXML parse(InputStream is)
	{
		return null;
	}
	
	public abstract String XMLtoString();

}
