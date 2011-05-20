package uplib;

import java.io.IOException;
import java.io.OutputStream;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;
import java.net.URLConnection;

import com.thoughtworks.xstream.XStream;
import com.thoughtworks.xstream.io.xml.DomDriver;

import upinterfaces.UPXMLEvent;

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
		URL url = new URL("http://" + this.host + ":" + this.port);
		HttpURLConnection conn = (HttpURLConnection) url.openConnection();
		conn.setRequestMethod("POST");
		conn.setDoOutput(true);
		
		XStream xs = new XStream(new DomDriver());
		xs.alias("event", UPXMLEvent.class);
		String xml = xs.toXML(event);
		System.out.println(xml);
		
		conn.setRequestProperty( "Content-type", "text/xml" );
		conn.setRequestProperty( "Content-length", Integer.toString(xml.length()));
		
		OutputStream ost = conn.getOutputStream();
		PrintWriter pw = new PrintWriter(ost);
		pw.print(xml);
		pw.flush();
		pw.close();
	}
}
