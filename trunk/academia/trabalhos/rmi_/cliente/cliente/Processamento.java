package cliente;

import java.io.Serializable;
import java.math.BigDecimal;
import interfaces.Tarefa;

public class Processamento implements Tarefa<BigDecimal>, Serializable {

	private static final long serialVersionUID = 227L;

	public BigDecimal executa()
	{
		return BigDecimal.valueOf(42);
	}

}
