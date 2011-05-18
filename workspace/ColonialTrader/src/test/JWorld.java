package test;

import java.awt.*;
import java.awt.event.*;
import java.awt.geom.Ellipse2D;

import javax.swing.*;

import trader.*;

@SuppressWarnings("serial")
public class JWorld extends JPanel implements MouseListener {

	private final World world;
	private final Captain captain;
	private JCity jcity;

	public JWorld(Captain captain, World world) {
		this.world = world;
		this.captain = captain;
		this.jcity = new JCity();
		addMouseListener(this);
	}
	
	@Override
	public void paint(Graphics g) 
	{
		super.paint(g);
		setBackground(Color.WHITE);
		
		Graphics2D g2d = (Graphics2D)g;

		g2d.setPaint(Color.lightGray);
		for(int x=0; x<world.w; x++)
			for(int y=0; y<world.h; y++)
				if(world.land[x][y])
					g2d.fill(new Rectangle(x * 4, y * 4, 4, 4));
		
		g2d.setPaint(Color.black);
		for(City city: world.cities)
			g2d.drawRect((int)city.coordinates.x * 4, (int)city.coordinates.y * 4, 4, 4);
		
		Ellipse2D.Double range = new Ellipse2D.Double(
				captain.docked.coordinates.x * 4 - (captain.ship.getRange() / 2),
				captain.docked.coordinates.y * 4 - (captain.ship.getRange() / 2),
				captain.ship.getRange(), captain.ship.getRange());
		g2d.setPaint(Color.lightGray);
		g2d.draw(range);
	}

	@Override
	public void mouseClicked(MouseEvent e) 
	{
		for(City city: world.cities)
			if(e.getX() >= (int)city.coordinates.x - 8 && e.getX() < (int)city.coordinates.x + 8
			&& e.getY() >= (int)city.coordinates.y - 8 && e.getY() < (int)city.coordinates.y + 8)
			{
				jcity.showCity(city);
				repaint();
				break;
			}
	}

	public void mouseEntered(MouseEvent arg0)  { }
	public void mouseExited(MouseEvent arg0)   { }
	public void mousePressed(MouseEvent arg0)  { }
	public void mouseReleased(MouseEvent arg0) { }

}
