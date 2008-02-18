#include "preferencias.h"
#include "palmincludes.h"
#include "database.h"
#include "aplicativo.h"

int Preferencias::ler(void* dados)
{
	UInt16 size;
	if(PrefGetAppPreferences(DB_CREATOR, app->numeroAplicativo(), dados, &size, false) == noPreferenceFound)
		return 0;
	else
		return size;
}

void Preferencias::salvar(void* dados, int size)
{
	PrefSetAppPreferences(DB_CREATOR, app->numeroAplicativo(), 1, dados, size, false);
}
