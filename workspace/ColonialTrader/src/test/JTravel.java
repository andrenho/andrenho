package test;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.BoxLayout;
import javax.swing.JButton;
import javax.swing.JDialog;
import javax.swing.JLabel;

import trader.Captain;
import trader.EnemyShip;
import trader.EnemyShip.CaptainType;
import trader.TravelInterface;

@SuppressWarnings("serial")
public class JTravel extends JDialog implements TravelInterface, ActionListener {

	JLabel shipInfo = new JLabel();
	JButton attack = new JButton("Attack"), 
	        flee = new JButton("Flee / Ignore"), 
	        surrender = new JButton("Surrender"), 
	        trade = new JButton("Trade"), 
	        bribe = new JButton("Bribe");
	private EnemyShip ship;

	public JTravel()
	{
		setModalityType(ModalityType.APPLICATION_MODAL);
		setLayout(new BoxLayout(getContentPane(), BoxLayout.Y_AXIS));
		JButton[] buttons = { attack, flee, surrender, trade, bribe };
		add(shipInfo);
		for(JButton b: buttons)
		{
			add(b);
			b.addActionListener(this);
		}
	}
	
	private void updateShipInfo()
	{
		shipInfo.setText(ship.captainType.toString() + "/" + ship.shipClass.name + " (" + ship.integrity + ")");
	}
	
	@Override
	public void encounter(EnemyShip s) 
	{
		this.ship = s;
		
		updateShipInfo();
		if(s.captainType == CaptainType.PIRATE)
		{
			surrender.setEnabled(true);
			trade.setEnabled(false);
			bribe.setEnabled(false);
		}
		else if(s.captainType == CaptainType.GOVERNMENT)
		{
			surrender.setEnabled(true);
			trade.setEnabled(false);
			bribe.setEnabled(true);
		}
		else if(s.captainType == CaptainType.MERCHANT)
		{
			surrender.setEnabled(false);
			trade.setEnabled(true);
			bribe.setEnabled(false);
		}
		else
			assert false;
		
		pack();
		setVisible(true);
	}

	@Override
	public void actionPerformed(ActionEvent e) {
		if(e.getSource().equals(attack))
			Captain.getCaptain().ship.attack(ship);
		
		updateShipInfo();
		if(Captain.getCaptain().ship.integrity <= 0 || ship.integrity <= 0)
			this.setVisible(false);
	}

}
