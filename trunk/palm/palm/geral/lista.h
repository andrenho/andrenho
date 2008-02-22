#ifndef LISTA_H
#define LISTA_H

#include "palmincludes.h"

typedef struct
{
	int reg;
	Char* string;
	void* proximo;
} Registro;

class Lista
{
public:
	Lista();
	~Lista();

	void adicionaRegistro(int reg, char* texto);
	int numeroRegistros();
	void stringLista(Char** s);
private:
	Registro* lista;
};

#endif
