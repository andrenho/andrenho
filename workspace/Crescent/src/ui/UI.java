package ui;

import game.*;

import java.applet.Applet;
import java.awt.Graphics;

@SuppressWarnings("serial")
public class UI extends Applet {

	private Game game;
	int rx, ry = 0;

	@Override
	public void init() {
		game = new Game(20, 20);
	}

	@Override
	public void start() {
	}

	@Override
	public void paint(Graphics g) {
		for(int x=0; x<getWidth() / 8; x++)
			for(int y=0; y<getHeight() / 8; y++)
			{
				drawTile(x+rx, y+ry, 
			}
	}
	
	

}
