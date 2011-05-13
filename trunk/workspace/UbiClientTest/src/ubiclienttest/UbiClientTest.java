package ubiclienttest;

import javax.swing.*;

import java.awt.event.*;

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
		
		// frame
		manager = new ClientManager(this);
		add(manager);
		
		pack();
	}

	@Override
	public void actionPerformed(ActionEvent e) {
		if(e.getSource().equals(novoCliente))
			manager.addClient();
	}

}
