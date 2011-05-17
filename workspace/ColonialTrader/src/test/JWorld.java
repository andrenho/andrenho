package test;

import java.awt.*;
import java.awt.geom.Ellipse2D;

import javax.swing.*;

import trader.*;

@SuppressWarnings("serial")
public class JWorld extends JPanel {

	private final World world;
	private final Captain captain;

	public JWorld(Captain captain, World world) {
		this.world = world;
		this.captain = captain;
	}
	
	@Override
	public void paint(Graphics g) {
		super.paint(g);
		
		Graphics2D g2d = (Graphics2D)g;
		for(City city: world.cities)
			g2d.drawRect((int)city.coordinates.x - 2, (int)city.coordinates.y - 2, 4, 4);
		
		Ellipse2D.Double range = new Ellipse2D.Double(
				captain.docked.coordinates.x - (captain.ship.getRange() / 2),
				captain.docked.coordinates.y - (captain.ship.getRange() / 2),
				captain.ship.getRange(), captain.ship.getRange());
		g2d.draw(range);
	}

}
