package ubiclienttest;

import java.awt.*;
import java.awt.event.*;
import java.util.Vector;

import javax.swing.*;

@SuppressWarnings("serial")
class ClientManager extends JLayeredPane implements MouseMotionListener {
	
	private Vector<ClientRepresentation> clients = new Vector<ClientRepresentation>();
	public Vector<ClientRepresentation> getClients() {
		return clients;
	}

	private Vector<Context> contexts;

	public ClientManager(UbiClientTest frame)
	{
		setPreferredSize(new Dimension(600, 400));
		
		// create contexts
		contexts = new Vector<Context>();
		contexts.add(new Context("Contexto 1", new Rectangle(50, 50, 150, 150)));
		contexts.add(new Context("Contexto 2", new Rectangle(300, 100, 200, 200)));
		contexts.add(new Context("Contexto 3", new Rectangle(200, 230, 200, 100)));
		
		// create contexts onscreen
		for(Context context: contexts)
		{
			JLabel label = new JLabel(context.nome);
			label.setBounds(context.rectangle);
			label.setBorder(BorderFactory.createLineBorder(Color.black));
			this.add(label, 1);
		}
		
		addMouseMotionListener(this);
	}

	@Override
	public void mouseDragged(MouseEvent e) {
		for(ClientRepresentation c: clients) 
		{
			if(c.getBounds().contains(e.getX(), e.getY()))
			{
				c.setLocation(e.getX() - (c.getBounds().width / 2), 
						e.getY() - (c.getBounds().height / 2));
				c.checkContext(contexts);
			}
		}
	}

	@Override
	public void mouseMoved(MouseEvent e) { }

	public ClientRepresentation addClient() {
		ClientRepresentation cr = new ClientRepresentation();
		clients.add(cr);
		add(cr);
		return cr;
	}
	
}
