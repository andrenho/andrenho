package uplib;

import java.io.BufferedReader;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.net.HttpURLConnection;
import java.net.URL;

import upinterfaces.InvalidXMLException;
import upinterfaces.UPXMLEvent;
import upinterfaces.UPXMLInferredData;

import com.thoughtworks.xstream.XStream;
import com.thoughtworks.xstream.io.xml.DomDriver;

public class UPConnection {

	private String host;
	private int port;

	public UPConnection(String host, int port)
	{
		this.host = host;
		this.port = port;
	}
	
	public void sendEvent(UPXMLEvent event) throws Exception
	{
		URL url = new URL("http://" + this.host + ":" + this.port + "/event/");
		HttpURLConnection conn = (HttpURLConnection) url.openConnection();
		conn.setRequestMethod("POST");
		conn.setDoInput(true);
		conn.setDoOutput(true);
		
		XStream xs = new XStream(new DomDriver());
		xs.alias("event", UPXMLEvent.class);
		String xml = xs.toXML(event);
		
		conn.setRequestProperty( "Content-type", "text/xml" );
		conn.setRequestProperty( "Content-length", Integer.toString(xml.length()));
		
		OutputStream ost = conn.getOutputStream();
		PrintWriter pw = new PrintWriter(ost);
		pw.print(xml);
		pw.flush();
		pw.close();
		
		InputStream is = conn.getInputStream();
	    BufferedReader rd = new BufferedReader(new InputStreamReader(is));
	    String line;
	    StringBuffer response = new StringBuffer(); 
	    while((line = rd.readLine()) != null) {
	      response.append(line);
	      response.append('\r');
	    }
	    rd.close();
	}
	
	public double infer(String user) throws Exception
	{
		URL url = new URL("http://" + this.host + ":" + this.port + "/inference/" + user + "/");
		HttpURLConnection conn = (HttpURLConnection) url.openConnection();
		//conn.setRequestMethod("GET");
		//conn.setDoInput(true);
		//conn.setDoOutput(true);
		
		/*
		XStream xs = new XStream(new DomDriver());
		xs.alias("event", UPXMLEvent.class);
		String xml = xs.toXML(event);
		
		conn.setRequestProperty( "Content-type", "text/xml" );
		conn.setRequestProperty( "Content-length", Integer.toString(xml.length()));
		
		OutputStream ost = conn.getOutputStream();
		PrintWriter pw = new PrintWriter(ost);
		pw.print("");
		pw.flush();
		pw.close();
		BufferedReader in = new BufferedReader(
                new InputStreamReader(
                conn.getInputStream()));
String inputLine;

while ((inputLine = in.readLine()) != null) 
System.out.println(inputLine);
in.close();
return 0.0;
		*/

		InputStream is = conn.getInputStream();
	    BufferedReader rd = new BufferedReader(new InputStreamReader(is));
	    String line;
	    StringBuffer response = new StringBuffer(); 
	    while((line = rd.readLine()) != null) {
	      response.append(line);
	      response.append('\r');
	    }
	    rd.close();
		
		XStream xs = new XStream(new DomDriver());
		xs.alias("inference", UPXMLInferredData.class);
		UPXMLInferredData data = null;
		try {
			data = (UPXMLInferredData)xs.fromXML(response.toString());
		} catch(Exception e) {
			throw new InvalidXMLException(e);
		}
		return data.value;
	}
}
