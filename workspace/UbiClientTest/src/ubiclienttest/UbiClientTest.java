package ubiclienttest;

import javax.swing.*;

import uplib.UPConnection;

import java.awt.event.*;
import java.rmi.NotBoundException;
import java.rmi.RemoteException;

@SuppressWarnings("serial")
public class UbiClientTest extends JFrame implements ActionListener {
	
	public static void main(String[] args) {
		SwingUtilities.invokeLater(new Runnable() { 
			public void run() { 
				(new UbiClientTest()).setVisible(true);
			} 
		});
	}

	private ClientManager manager;
	private JMenuItem novoCliente;
	private JMenu inferenceMenu;

	public UbiClientTest()
	{
		super("UbiClientTest");
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		// menubar
		JMenuBar menubar = new JMenuBar();
		JMenu menu = new JMenu("Opções");
		novoCliente = new JMenuItem("Novo Cliente");
		novoCliente.addActionListener(this);
		menu.add(novoCliente);
		menubar.add(menu);
		setJMenuBar(menubar);
		
		inferenceMenu = new JMenu("Inferir");
		menubar.add(inferenceMenu);
		
		// frame
		manager = new ClientManager(this);
		add(manager);
		
		pack();
	}

	@Override
	public void actionPerformed(ActionEvent e) {
		if(e.getSource().equals(novoCliente))
		{
			ClientRepresentation cr = null;
			try {
				cr = manager.addClient();
			} catch (Exception e2) {
				e2.printStackTrace();
				return;
			}
			JMenuItem mi = new JMenuItem(cr.name.toString());
			inferenceMenu.add(mi);
			mi.addActionListener(new ActionListener() {
				
				@Override
				public void actionPerformed(ActionEvent e) {
					for(ClientRepresentation cr: manager.getClients())
						if(((JMenuItem)e.getSource()).getText().equals(cr.name.toString()))
						{
							try {
								double v = (new UPConnection("localhost", 8080)).infer(cr.name.toString());
								JOptionPane.showMessageDialog(UbiClientTest.this, "Trocas de contexto: " + v);
							} catch (Exception e1) {
								e1.printStackTrace();
							}
						}
				}
			});
		}
	}

}
