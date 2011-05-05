package br.unisinos.ubiperson.command;

import java.io.IOException;
import java.io.InputStream;

import org.xml.sax.Attributes;
import org.xml.sax.InputSource;
import org.xml.sax.SAXException;
import org.xml.sax.XMLReader;
import org.xml.sax.helpers.DefaultHandler;
import org.xml.sax.helpers.XMLReaderFactory;

public class UserXMLCommand extends DefaultHandler  
{
	public String name, password;
	
	public static UserXMLCommand parse(InputStream is) throws SAXException, IOException 
	{
		UserXMLCommand user = new UserXMLCommand();
		XMLReader xr = XMLReaderFactory.createXMLReader();
		xr.setContentHandler(user);
		xr.parse(new InputSource(is));
		return user;
	}
	
	public void startElement (String uri, String name,
		      String qName, Attributes atts)
	{
		if ("".equals (uri))
			System.out.println("Start element: " + qName);
		else
			System.out.println("Start element: {" + uri + "}" + name);
	}
}

