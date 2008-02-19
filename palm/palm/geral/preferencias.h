#ifndef PREFERENCIAS_H
#define PREFERENCIAS_H

#include "aplicativo.h"

class Preferencias
{
public:
	int tamanhoDados(int numeroAplicativo);
	int tamanhoDados() { return tamanhoDados(app->numeroAplicativo); }
	bool ler(int numeroAplicativo, void* dados);
	bool ler(void* dados) { return ler(app->numeroAplicativo, dados); }
	void salvar(void* dados, int size);
};

#endif
