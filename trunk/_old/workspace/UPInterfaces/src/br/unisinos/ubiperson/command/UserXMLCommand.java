package br.unisinos.ubiperson.command;

import java.io.IOException;
import java.io.InputStream;

import org.xml.sax.Attributes;
import org.xml.sax.SAXException;

public class UserXMLCommand extends XMLCommand
{
	public String name, password;
	
	public UserXMLCommand(String name, String password)
	{
		this.name = name;
		this.password = password;
	}
	
	public UserXMLCommand(InputStream is) throws SAXException, IOException {
		super(is);
	}

	public void startElement (String uri, String name, String qName, Attributes atts)
		throws SAXException
	{
		if(qName == "user")
		{
			this.name = atts.getValue("name");
			this.password = atts.getValue("password");
		}
		else
			throw new SAXException();
	}

	public String getXML() {
		return "<?xml version=\"1.0\"?><user name=\"" + name + "\" password=\"" + password + "\" />";
	}
}

