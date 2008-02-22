#ifndef PREFERENCIAS_H
#define PREFERENCIAS_H

#include "aplicativo.h"
#include "segment.h"

class Preferencias
{
public:
	int tamanhoDados(int numeroAplicativo) GERAL;
	int tamanhoDados() { return tamanhoDados(app->numeroAplicativo); }
	bool ler(int numeroAplicativo, void* dados) GERAL;
	bool ler(void* dados) { return ler(app->numeroAplicativo, dados); }
	void salvar(void* dados, int size) GERAL;
};

#endif
