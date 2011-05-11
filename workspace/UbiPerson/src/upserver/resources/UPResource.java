package upserver.resources;

import com.sun.net.httpserver.*;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.util.Arrays;

import com.sun.net.httpserver.HttpExchange;
import com.thoughtworks.xstream.XStream;

import upinterfaces.*;
import upserver.UPServices;

public abstract class UPResource implements HttpHandler {
	
	public UPServices services;
	public XStream xstream;
	
	protected UPResponse get(String[] parameters)
	{
		return invalidMethod("GET");
	}

	protected UPResponse post(String[] parameters, String message)
	{
		return invalidMethod("POST");
	}

	protected UPResponse put(String[] parameters, String message)
	{
		return invalidMethod("PUT");
	}

	protected UPResponse delete(String[] parameter)
	{
		return invalidMethod("DELETE");
	}

	protected UPResponse invalidMethod(String method) {
		return new UPResponse(405, new UPXMLSimpleMessage("Method " + method + " not allowed."));
	}

	@Override
	public void handle(HttpExchange t) throws IOException {
		String method = t.getRequestMethod();
		
		String[] parameters = t.getRequestURI().toString().split("/");
		parameters = Arrays.copyOfRange(parameters, 1, parameters.length);
		
		String request = "";
		if(method.equals("POST") || method.equals("PUT"))
		{
			InputStream is = t.getRequestBody();
			BufferedReader in = new BufferedReader(new InputStreamReader(is));
			StringBuffer sb = new StringBuffer();
			String s;
			while((s = in.readLine()) != null)
				sb.append(s);
			in.close();
			request = sb.toString();
		}
		
		UPResponse response = null;
		if(method.equals("GET"))
			response = get(parameters);
		else if(method.equals("DELETE"))
			response = delete(parameters);
		else if(method.equals("POST"))
			response = post(parameters, request);
		else if(method.equals("PUT"))
			response = put(parameters, request);
		else
			response = invalidMethod(method);
		
		String message = response.message.XMLtoString();
		t.sendResponseHeaders(response.code, message.length());
		OutputStream os = t.getResponseBody();
		os.write(message.getBytes());
		os.close();
	}

}
