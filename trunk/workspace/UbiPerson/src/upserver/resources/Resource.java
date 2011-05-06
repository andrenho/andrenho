package upserver.resources;

public class Resource {

	public String path;
	public Class resouce;
		
	public Resource(String path, Class resource)
	{
		this.path = path;
		this.resouce = resource;
	}
	
	public static Resource[] resources = {
		new Resource("/event", Event.class)
	};
}
