import java.util.Comparator;


public class ChamadoTempo implements Comparator<ChamadoTempo> {

	Chamado chamado;
	double tempo;
	
	public ChamadoTempo(Chamado chamado, double tempo)
	{
		this.chamado = chamado;
		this.tempo = tempo;
	}

	@Override
	public int compare(ChamadoTempo o1, ChamadoTempo o2) {
		if(o1.tempo < o2.tempo)
			return -1;
		else if(o1.tempo > o2.tempo)
			return 1;
		else
			return 0;
	}
	
}
