package ui;

import java.applet.Applet;
import java.awt.*;
import java.awt.geom.*;
import java.util.Timer;
import java.util.TimerTask;

import city.*;

public class UI extends Applet {

	private static final long serialVersionUID = 254L;
	private City city;
	private double rx = 0.0, ry = 0.0;
	private Timer timer;

	@Override
	public void init() {
		city = new City();
		timer = new Timer();
	}

	@Override
	public void start() {
		timer.schedule(new Tick(), 1000/60, 1000/60);
	}
	
	private class Tick extends TimerTask {
		@Override
		public void run() { 
			city.tick();
			repaint();
		}
	}

	@Override
	public void paint(Graphics g) {
		// Initialize Graphics2D
		Graphics2D g2 = (Graphics2D)g;
		RenderingHints rh = new RenderingHints(
				RenderingHints.KEY_ANTIALIASING,
				RenderingHints.VALUE_ANTIALIAS_ON);
		g2.setRenderingHints(rh);
		
		drawGrid(g2);
		
		// draw people
		for(Person p: city.people)
			drawPerson(g2, p);
	}

	private void drawGrid(Graphics2D g) {
		for(int x=0; x<this.getWidth(); x += 10)
			for(int y=0; y<this.getHeight(); y += 10)
				g.draw(new Point2D.Double(x, y));
	}

	private void drawPerson(Graphics2D g, Person p) {
		g.draw(new Ellipse2D.Double(p.x+rx, p.y+ry, 4, 4));
	}

}
