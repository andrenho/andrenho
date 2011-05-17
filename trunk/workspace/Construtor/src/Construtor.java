import java.awt.*;
import java.awt.event.*;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;

import javax.swing.*;

@SuppressWarnings("serial")
public class Construtor extends JFrame implements ActionListener {

	private Fase fase = null;
	private JMenuItem novo, abrir, salvar;
	private final JFileChooser fc = new JFileChooser();

	public Construtor()
	{
		super("Construtor");
		setDefaultCloseOperation(EXIT_ON_CLOSE);
		
		criaMenus();
		setPreferredSize(new Dimension(600, 400));
		
		pack();
	}
	
	private void criaMenus() 
	{
		JMenuBar menubar = new JMenuBar();
		JMenu arquivo = new JMenu("Arquivo");
		JMenu desenho = new JMenu("Desenho");
		
		arquivo.add(novo = new JMenuItem("Novo"));
		arquivo.add(abrir = new JMenuItem("Abrir"));
		arquivo.add(salvar = new JMenuItem("Salvar"));

		novo.addActionListener(this);
		abrir.addActionListener(this);
		salvar.addActionListener(this);

		for(TipoComponente tipo: TipoComponente.lista)
		{
			JMenu menu = new JMenu(tipo.nome);
			for(Componente componente: Componente.lista)
				if(componente.tipo == tipo)
				{
					JMenuItem item = new JMenuItem(componente.nome);
					item.addActionListener(this);
					menu.add(item);
				}
			desenho.add(menu);
		}
		
		menubar.add(arquivo);
		menubar.add(desenho);
		setJMenuBar(menubar);
	}

	public static void main(String[] args)
	{
		javax.swing.SwingUtilities.invokeLater(new Runnable() {
            public void run() {
                Construtor construtor = new Construtor();
                construtor.setVisible(true);
            }
        });
	}

	@Override
	public void actionPerformed(ActionEvent e) 
	{
		if(e.getSource().equals(novo))
		{
			if(fase != null && fase.dirty)
			{
				int n = JOptionPane.showConfirmDialog(this, "Fase não salva. Confirma?", 
						"Confirma", JOptionPane.YES_NO_OPTION);
				if(n != JOptionPane.YES_OPTION)
					return;
			}
			fase = new Fase(100, 50);
			JScrollPane scroll = new JScrollPane(fase);
			add(scroll);
			pack();
		}
		else if(e.getSource().equals(abrir))
		{
			int r = fc.showOpenDialog(this);
			if(r == JFileChooser.APPROVE_OPTION)
			{
				File f = fc.getSelectedFile();
				try {
					FileInputStream fs = new FileInputStream(f);
					fase = Fase.carregar(fs);
					JScrollPane scroll = new JScrollPane(fase);
					add(scroll);
					pack();					
				} catch (FileNotFoundException e1) {
					e1.printStackTrace();
				}
			}
		}
		else if(e.getSource().equals(salvar))
		{
			if(fase == null)
				return;
			int r = fc.showSaveDialog(this);
			if(r == JFileChooser.APPROVE_OPTION)
			{
				File f = fc.getSelectedFile();
				try {
					FileOutputStream fs = new FileOutputStream(f);
					fase.salvar(fs);
					fs.close();
				} catch (FileNotFoundException ex) {
					ex.printStackTrace();
				} catch (IOException ex) {
					ex.printStackTrace();
				}
			}
		}
		else
			for(Componente componente: Componente.lista)
				if(e.getSource() instanceof JMenuItem && ((JMenuItem)e.getSource()).getText().equals(componente.nome))
					if(fase != null)
					{
						fase.selecionado = componente;
						fase.tipoSelecionado = componente.tipo;
					}
	}
	
}
