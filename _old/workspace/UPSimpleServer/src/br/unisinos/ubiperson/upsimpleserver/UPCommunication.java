package br.unisinos.ubiperson.upsimpleserver;

import java.io.IOException;
import java.net.InetSocketAddress;
import com.sun.net.httpserver.HttpServer;

import br.unisinos.ubiperson.upsimpleserver.handlers.*;

public class UPCommunication {
	
	protected HttpServer server;
	protected UPServices services;
	protected UPAuthentication auth;
	
	public UPCommunication(UPAuthentication auth, UPServices services) {
		this.services = services;
		this.auth = auth;
	}

	public void run() throws IOException
	{
		server = HttpServer.create(new InetSocketAddress(8080), 0); // TODO - https
		server.createContext("/user", new UserHandler(auth));
		server.setExecutor(null);
		server.start();
		System.out.println("Servidor iniciado.");
	}
	
}
