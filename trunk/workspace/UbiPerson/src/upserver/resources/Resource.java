package upserver.resources;

import upserver.UPServices;

public class Resource {

	public String path;
	public Class resource;
		
	public Resource(String path, Class resource)
	{
		this.path = path;
		this.resource = resource;
	}
	
	public UPResource newInstance(UPServices services) throws InstantiationException, IllegalAccessException
	{
		UPResource r = (UPResource)resource.newInstance();
		r.services = services;
		return r;
	}
	
	public static Resource[] resources = {
		new Resource("/event", Event.class)
	};
}
