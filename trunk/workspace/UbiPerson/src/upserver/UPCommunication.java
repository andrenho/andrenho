package upserver;

import java.io.IOException;
import java.net.InetSocketAddress;
import com.sun.net.httpserver.HttpServer;

import upserver.resources.*;


public class UPCommunication {
	
	private UPServices services;
	private int port;
	private HttpServer server;

	public UPCommunication(UPServices services, int port)
	{
		this.services = services;
		this.port = port;
	}
	
	public void run() throws IOException, InstantiationException, IllegalAccessException
	{
		server = HttpServer.create(new InetSocketAddress(this.port), 0); // TODO - https
		for(Resource r: Resource.resources)
			server.createContext(r.path, (UPResource)r.resouce.newInstance());
		server.setExecutor(null);
		server.start();
		System.out.println("Servidor iniciado.");
	}
}
