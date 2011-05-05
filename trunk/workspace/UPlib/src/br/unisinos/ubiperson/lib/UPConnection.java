package br.unisinos.ubiperson.lib;

import java.io.BufferedReader;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.*;

public class UPConnection {
	
	public UPConnection(URL url, String name, String password)
	{
		
	}
	
	
	public static void createUser(URL url, String name, String password) throws IOException
	{
		System.out.println(request(url, "POST", "<?xml version=\"1.0\"><user name=\"" + name + "\" password=\"" + password + "\" />"));
	}

	private static String request(URL url, String method, String data) throws IOException
	{
		HttpURLConnection c = (HttpURLConnection)url.openConnection();
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
	    return response.toString();
	}
	
	public static void main(String[] args) throws MalformedURLException, IOException
	{
		UPConnection.createUser(new URL("http://localhost:8080/user"), "name", "1234");
	}
}
