
public class FilaUsuario extends Fila {

	public Fila erroManutencao, erroProjeto;
	
	public FilaUsuario(Fila proximaOk, int numeroFilas, double taxaAtendimento) {
		super(proximaOk, 1, taxaAtendimento);
		
	}

}
