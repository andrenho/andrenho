package br.unisinos.ubiperson.lib;

import java.io.BufferedReader;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.*;

import br.unisinos.ubiperson.command.UserXMLCommand;

public class UPConnection {
	
	private static class ServerResponse {
		int code;
		String message;
		public String toString() {
			return code + " - " + message;
		}
	}
	
	public UPConnection(String url, String name, String password) throws IOException
	{
		System.out.println(request(url + "/login", "POST", 
				(new UserXMLCommand(name, password)).getXML()));
	}
	
	
	public static void createUser(String url, String name, String password) throws IOException
	{
		System.out.println(request(url + "/user", "POST", 
				(new UserXMLCommand(name, password)).getXML()));
	}

	private static ServerResponse request(String url, String method, String data) throws IOException
	{
		HttpURLConnection c = (HttpURLConnection)(new URL(url)).openConnection();
		c.setRequestMethod(method);
		c.setRequestProperty("Content-Type", "text/xml");
		c.setRequestProperty("Content-Length", "" +
	               Integer.toString(data.getBytes().length));
		c.setUseCaches (false);
	    c.setDoInput(true);
	    c.setDoOutput(true);

	    DataOutputStream wr = new DataOutputStream (c.getOutputStream ());
	    wr.writeBytes (data);
	    wr.flush ();
	    wr.close ();
	    
	    InputStream is = c.getInputStream();
	    BufferedReader rd = new BufferedReader(new InputStreamReader(is));
	    String line;
	    StringBuffer response = new StringBuffer(); 
	    while((line = rd.readLine()) != null) {
	        response.append(line);
	        response.append('\r');
	    }
	    rd.close();
	    
	    ServerResponse sr = new ServerResponse();
	    sr.code = c.getResponseCode();
	    sr.message = response.toString(); 
	    return sr;
	}
	
	public static void main(String[] args) throws MalformedURLException, IOException
	{
		UPConnection.createUser("http://localhost:8080", "name", "1234");
		//new UPConnection("http://localhost:8080", "name", "1234");
	}
}
