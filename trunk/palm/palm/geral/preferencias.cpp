#include "preferencias.h"
#include "palmincludes.h"
#include "database.h"
#include "aplicativo.h"

int Preferencias::tamanhoDados(int numeroAplicativo)
{
	UInt16 size = 0;
	int n;
	n = PrefGetAppPreferences(DB_CREATOR, 1 /*numeroAplicativo*/, NULL, &size, false);
	if(n == noPreferenceFound)
		return 0;
	else
		return size;
}

bool Preferencias::ler(int numeroAplicativo, void* dados)
{
	UInt16 size;
	Int16 n;
	size = tamanhoDados(numeroAplicativo);
	n = PrefGetAppPreferences(DB_CREATOR, 1 /*numeroAplicativo*/, dados, &size, false);
	if(n == noPreferenceFound)
	{
		dados = NULL;
		return false;
	}
	else
		return true;
}

void Preferencias::salvar(void* dados, int size)
{
	PrefSetAppPreferences(DB_CREATOR, 1 /*app->numeroAplicativo*/, 1, dados, size, false);
}
