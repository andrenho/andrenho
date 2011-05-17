import java.awt.*;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.HashMap;

import javax.swing.*;

@SuppressWarnings("serial")
public class Fase extends JPanel implements MouseListener {
	
	private int w;
	private int h;
	private static final int tileSize = 16;
	public HashMap<TipoComponente, Componente[][]> mapa = new HashMap<TipoComponente, Componente[][]>();
	public TipoComponente tipoSelecionado = null;
	public Componente selecionado = null;
	public boolean dirty = false;

	public Fase(int w, int h)
	{
		this.w = w;
		this.h = h;
		
		for(TipoComponente tipo: TipoComponente.lista)
		{
			mapa.put(tipo, new Componente[w][h]);
			for(int x=0; x<w; x++)
				for(int y=0; y<h; y++)
					mapa.get(tipo)[x][y] = null;
		}

		setPreferredSize(new Dimension(w * tileSize, h * tileSize));
		addMouseListener(this);
	}
	
	@Override
	public void paintComponent(Graphics g) {
		super.paintComponent(g);
		setBackground(Color.white);
		Graphics2D g2d = (Graphics2D)g;
		
		for(TipoComponente tipo: TipoComponente.lista)
			for(int x=0; x<w; x++)
				for(int y=0; y<h; y++)
				{
					Componente comp = mapa.get(tipo)[x][y];
					if(comp != null)
					{
						g2d.setPaint(comp.cor);
						g2d.fill(new Rectangle(x*tileSize, y*tileSize, tileSize, tileSize));
					}
				}

		g2d.setColor(Color.black);
		for(int x=0; x<w*tileSize; x+=tileSize)
			for(int y=0; y<h*tileSize; y+=tileSize)
				g2d.drawLine(x, y, x, y);
	}

	@Override
	public void mouseClicked(MouseEvent e) 
	{
		int x = e.getX() / tileSize;
		int y = e.getY() / tileSize;
		if(e.getButton() == MouseEvent.BUTTON1)
		{
			if(tipoSelecionado != null && selecionado != null)
			{
				dirty = true;
				mapa.get(tipoSelecionado)[x][y] = selecionado;
			}
		}
		else if(e.getButton() == MouseEvent.BUTTON3)
			for(TipoComponente tipo: TipoComponente.lista)
				mapa.get(tipo)[x][y] = null;
		repaint(x * tileSize, y * tileSize, tileSize, tileSize);
	}
	
	public static Fase carregar(InputStream is)
	{
		return null; // TODO
	}
	
	public void salvar(OutputStream os)
	{
		try {
			// verifica tamanho do mapa
			int min_w = 0, min_h = 0;
			for(TipoComponente tipo: TipoComponente.lista)
				for(int x=0; x<w; x++)
					for(int y=0; y<h; y++)
						if(mapa.get(tipo)[x][y] != null)
						{
							if(x > min_w)
								min_w = x + 1;
							if(y > min_h)
								min_h = y + 1;
						}

			// salva objetos
			for(int x=0; x<w; x++)
				for(int y=0; y<h; y++)
				{
					Componente c = mapa.get(TipoComponente.OBJETO)[x][y];
					if(c != null)
					{
						String s = c.codigo + " " + x + " " + y + "\n";
						os.write(s.getBytes());
					}
				}
			
			os.write("--".getBytes());
						
			// salva mapa
			for(int y=0; y<min_h; y++)
			{
				for(int x=0; x<min_w; x++)
				{
					Componente c = mapa.get(TipoComponente.SOLIDO)[x][y];
					if(c == null)
						os.write((int)' ');
					else
						os.write((int)c.codigo);
				}
				os.write((int)'\n');
			}		
			
		} catch (IOException e) {
			e.printStackTrace();
		}
		
	}

	public void mouseEntered(MouseEvent arg0) {	}
	public void mouseExited(MouseEvent arg0) { }
	public void mousePressed(MouseEvent arg0) { }
	public void mouseReleased(MouseEvent arg0) { }
	
}
