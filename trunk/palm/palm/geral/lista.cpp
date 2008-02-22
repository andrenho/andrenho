#include "lista.h"
#include "debug.h"

Lista::Lista()
{
	lista = NULL;
}

Lista::~Lista()
{
	Registro *r;

	while(lista != NULL)
	{
		MemPtrFree(lista->string);
		r = lista;
		lista = (Registro*)lista->proximo;
		MemPtrFree(r);
	}
}

void Lista::adicionaRegistro(int reg, char* texto)
{
	Registro *atual, *anterior;
	char* str = (char*)MemPtrNew(StrLen(texto)+1);
	StrCopy(str, texto);

	atual = lista;

	if(lista != NULL)
	{
		anterior = atual;
		while(atual->proximo != NULL)
		{
			anterior = atual;
			atual = (Registro*)atual->proximo;
		}
		atual = (Registro*)MemPtrNew(sizeof(Registro));
		anterior->proximo = atual;
	}
	else
	{
		atual = (Registro*)MemPtrNew(sizeof(Registro));
		lista = atual;
	}

	atual->reg = reg;
	atual->string = str;
	atual->proximo = NULL;
}

int Lista::numeroRegistros()
{
	Registro *r = lista;

	if(r)
	{
		int ct = 0;
		do
		{
			ct++;
			r = (Registro*)r->proximo;
		} while(r);
		return ct;
	}
	else
		return 0;
}

void Lista::stringLista(Char** s)
{
	Registro *r = lista;

	if(r)
	{
		int i = 0;
		r = lista;
		do
		{
			s[i] = r->string;
			r = (Registro*)r->proximo;
			i++;
		} while(r);
	}
	else
		s = NULL;
}
