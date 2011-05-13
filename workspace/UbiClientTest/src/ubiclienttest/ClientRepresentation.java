package ubiclienttest;

import java.awt.*;
import javax.swing.*;

@SuppressWarnings("serial")
public class ClientRepresentation extends JLabel {
	
	private static char letter = 'A';
	private static Color[] layerColors = { Color.yellow, Color.magenta,
            Color.cyan,   Color.red,
            Color.green };
	private static int color = 0;
	
	public ClientRepresentation()
	{
		super(String.valueOf(letter));
		
		setBounds(new Rectangle(10, 10, 25, 25));
		setBorder(BorderFactory.createLineBorder(Color.black));
		setOpaque(true);
		setBackground(layerColors[color]);

		letter += 1;
		color += 1;
		if(color > layerColors.length)
			color = 0;
	}
}
