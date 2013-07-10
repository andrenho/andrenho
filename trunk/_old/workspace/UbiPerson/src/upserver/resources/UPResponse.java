package upserver.resources;

import upinterfaces.UPXML;

public class UPResponse {

	public int code;
	public UPXML message;
	
	public UPResponse(int code, UPXML message)
	{
		this.code = code;
		this.message = message;
	}
	
}
