#include "preferencias.h"
#include "palmincludes.h"
#include "database.h"

int Preferencias::ler(void* dados)
{
	UInt16 size;
	if(PrefGetAppPreferences(DB_CREATOR, 0, dados, &size, false) == noPreferenceFound)
		return 0;
	else
		return size;
}

void Preferencias::salvar(void* dados, int size)
{
	PrefSetAppPreferences(DB_CREATOR, 0, 1, dados, size, false);
}
