package upinterfaces;

public class UPXMLSimpleMessage extends UPXML {

	private String message;

	public UPXMLSimpleMessage(String message)
	{
		this.message = message;
	}
	
	@Override
	public String XMLtoString() {
		return "<h1>" + message + "</h1>";
	}

}
