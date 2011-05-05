package br.unisinos.ubiperson.ontology;

import java.text.SimpleDateFormat;
import java.util.Calendar;

public class Event {

	public Calendar time; 
	public String name;
	
	public String createXML()
	{
		StringBuilder s = new StringBuilder();
		s.append("<?xml version=\"1.0\" encoding=\"UTF-8\" ?>\n");
		s.append("<event name=\"" + name + "\" time=\"" + 
				SimpleDateFormat.getDateTimeInstance().format(time) + "\">\n"); 
		s.append("</event>");
		return s.toString();
	}
	
}
