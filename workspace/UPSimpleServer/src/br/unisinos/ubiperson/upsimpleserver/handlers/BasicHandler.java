package br.unisinos.ubiperson.upsimpleserver.handlers;

import java.io.IOException;
import java.io.OutputStream;

import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;

public abstract class BasicHandler implements HttpHandler {
	
	protected void sendReply(HttpExchange t, int number, String response) throws IOException
	{
		t.sendResponseHeaders(number, response.length());
		OutputStream os = t.getResponseBody();
		os.write(response.getBytes());
		os.close();
	}
}
