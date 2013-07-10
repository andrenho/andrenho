#include "aplicativo.h"

Aplicativo* app;

Aplicativo::Aplicativo(int numeroAplicativo)
{
	Preferencias pref;
	int n;

	this->numeroAplicativo = numeroAplicativo;
	n = pref.tamanhoDados(numeroAplicativo);
	if(n > 0)
	{
		h = MemHandleNew(n);
		preferencias = MemHandleLock(h);
		pref.ler(numeroAplicativo, preferencias);
	}
	else
		preferencias = NULL;
}

void Aplicativo::executar(UInt16 cmd)
{
	appActive = true;

	frmType = NonModal;

	while(appActive)
		current->open();
	current->gravarPreferencias();
}

Aplicativo::~Aplicativo()
{
	FrmCloseAllForms();

	if(preferencias != NULL)
	{
		MemHandleUnlock(h);
		MemHandleFree(h);
	}
}
