package br.unisinos.ubiperson.upsimpleserver.handlers;

import java.io.IOException;
import java.io.OutputStream;

import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;

public abstract class BasicHandler implements HttpHandler {
	
	protected void sendReply(HttpExchange t, int code, String response) throws IOException
	{
		System.out.println("Resposta: " + code);
		t.sendResponseHeaders(code, response.length());
		OutputStream os = t.getResponseBody();
		os.write(response.getBytes());
		os.close();
	}
}
