#ifndef LISTA_H
#define LISTA_H

#include "palmincludes.h"
#include "segment.h"

typedef struct
{
	int reg;
	Char* string;
	void* proximo;
} Registro;

/** 
 * <p>Esta é uma classe que controla o uso de lista (ou popups) no Palm.</p>
 * 
 * <p>Na inicialização da classe do form, deve-se inicializar a lista e
 * adicionar os registros:</p>
 *
 * <pre>
 * l = new Lista();
 * l->adicionaRegistro(1, "Registro 1");
 * l->adicionaRegistro(2, "Registro 2");
 * </pre>
 *
 * <p>Ao mostrar o form na tela, deve-se chamar:</p>
 *
 * <pre>
 * l->setItensLista((ListType*)getControl(FinalizaPagamentoList), 10);
 * </pre>
 *
 * <p>E ao destruir a classe do form, não deve se esquecer de destruir a
 * classe da lista junto.</p> */
class Lista
{
public:
	/// Cria uma nova lista.
	Lista() GERAL;

	/// Destrói a lista e libera a memória.
	~Lista() GERAL;

	/// Adiciona um novo registro à lista.
	void adicionaRegistro(int reg, char* texto) GERAL;

	/** Coloca os registros na lista do form. Este método deve ser
	 *  chamado apenas quando o form fica visível. */
	void setItensLista(ListType* lista, int maxRegistrosVisiveis, bool autoAjusta) GERAL;

	/** Retorna a chave do registro selecionado, baseado na posição
	 *  na lista. 
	 *
	 *  @returns -1 se não foi encontrado. */
	int registro(int posicao) GERAL;
private:
	Char** ss;
	int numeroRegistros() GERAL;
	void stringLista(Char** s) GERAL;
	Registro* lista;
};

#endif
