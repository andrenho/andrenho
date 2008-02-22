#ifndef LISTA_H
#define LISTA_H

#include "palmincludes.h"

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
	Lista();

	/// Destrói a lista e libera a memória.
	~Lista();

	/// Adiciona um novo registro à lista.
	void adicionaRegistro(int reg, char* texto);

	/** Coloca os registros na lista do form. Este método deve ser
	 *  chamado apenas quando o form fica visível. */
	void setItensLista(ListType* lista, int maxRegistrosVisiveis);

	/** Retorna a chave do registro selecionado, baseado na posição
	 *  na lista. 
	 *
	 *  @returns -1 se não foi encontrado. */
	int registro(int posicao);
private:
	Char** ss;
	int numeroRegistros();
	void stringLista(Char** s);
	Registro* lista;
};

#endif
