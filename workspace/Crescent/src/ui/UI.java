package ui;

import game.*;

import java.applet.Applet;
import java.awt.Graphics;

@SuppressWarnings("serial")
public class UI extends Applet {

	private Game game;

	@Override
	public void init() {
		game = new Game(20, 20);
	}

	@Override
	public void start() {
	}

	@Override
	public void paint(Graphics g) {
		
	}
	
	

}
