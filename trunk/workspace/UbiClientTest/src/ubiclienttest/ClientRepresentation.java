package ubiclienttest;

import java.awt.*;
import java.util.Date;
import java.util.Vector;

import javax.swing.*;

import upinterfaces.UPXMLEvent;
import uplib.UPConnection;

@SuppressWarnings("serial")
public class ClientRepresentation extends JLabel {
	
	private static char letter = 'A';
	private static Color[] layerColors = { Color.yellow, Color.magenta,
            Color.cyan,   Color.red,
            Color.green };
	private static int color = 0;
	private Vector<Context> contexts = new Vector<Context>();
	public String name;
	private UPConnection connection;
	
	public ClientRepresentation()
	{
		super(String.valueOf(letter));
		name = String.valueOf(letter);
		
		setBounds(new Rectangle(10, 10, 25, 25));
		setBorder(BorderFactory.createLineBorder(Color.black));
		setOpaque(true);
		setBackground(layerColors[color]);

		letter += 1;
		color += 1;
		if(color > layerColors.length)
			color = 0;
		
		connection = new UPConnection("localhost", 8080);
	}

	public void checkContext(Vector<Context> contexts) {
		for(Context c: contexts)
			if(this.getBounds().intersects(c.rectangle))
			{
				if(!this.contexts.contains(c))
					enterContext(c);
			}
			else
				if(this.contexts.contains(c))
					leaveContext(c);
	}

	private void leaveContext(Context c) {
		contexts.remove(c);
		
		UPXMLEvent event = new UPXMLEvent();
		event.user = name;
		event.action = "leave";
		event.context = c.nome;
		event.date = new Date();
		try {
			connection.sendEvent(event);
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	private void enterContext(Context c) {
		contexts.add(c);

		UPXMLEvent event = new UPXMLEvent();
		event.user = name;
		event.action = "enter";
		event.context = c.nome;
		event.date = new Date();
		try {
			connection.sendEvent(event);
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
}
