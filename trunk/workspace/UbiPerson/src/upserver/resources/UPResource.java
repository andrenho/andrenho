package upserver.resources;

import com.sun.net.httpserver.*;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

import com.sun.net.httpserver.HttpExchange;
import upinterfaces.*;

public abstract class UPResource implements HttpHandler {
	
	protected UPResponse get(String[] parameters)
	{
		return invalidMethod("GET");
	}

	protected UPResponse post(String[] parameters, UPXML command)
	{
		return invalidMethod("POST");
	}

	protected UPResponse put(String[] parameters, UPXML command)
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
		
		UPResponse response = null;
		if(method.equals("GET"))
			response = get(parameters);
		else if(method.equals("DELETE"))
			response = delete(parameters);
		else if(method.equals("POST"))
		{
			InputStream is = t.getRequestBody();
			response = post(parameters, UPXML.parse(is));
		}
		else if(method.equals("PUT"))
		{
			InputStream is = t.getRequestBody();
			response = put(parameters, UPXML.parse(is));
		}
		else
			response = invalidMethod(method);
		
		String message = response.message.XMLtoString();
		t.sendResponseHeaders(response.code, message.length());
		OutputStream os = t.getResponseBody();
		os.write(message.getBytes());
		os.close();
	}

}
