#include "frmpedido.h"
#include "apppedidos.h"

typedef struct
{
	int numeroForm;
	char cnpj[CNPJ_CHARS];
	char fantasia[FANTASIA_CHARS];
	char razaoSocial[RAZAOSOCIAL_CHARS];
	int cidadeSelecionada;
	char cidadeLista[CIDADE_CHARS];
} PrefPedido;

FrmPedido::FrmPedido() : Form()
{
	nCidades = 0;
	cidadeSelecionada = -1;
	cidades = NULL;
	codCidades = NULL;
	id = PedidoFrm;
}

FrmPedido::~FrmPedido()
{
	int i;
	for(i=0; i<nCidades; i++)
		MemPtrFree(cidades[i]);
	if(cidades)
		MemPtrFree(cidades);
	if(codCidades)
		MemPtrFree(codCidades);
}

bool FrmPedido::event(UInt16 controlID, EventType* e)
{
	if(e->eType == ctlSelectEvent)
		switch(controlID)
		{
			case PedidoCancelar:
				goToForm(appPedidos->frmPrincipal);
				return true;
			case PedidoBuscaCliente:
				if(!appPedidos->buscaCliente->busca(this, PedidoCNPJ, PedidoCliente, PedidoRazaoSocial, cidadeSelecionada))
					setField(PedidoCNPJ, "");
				return true;
			case PedidoItens:
				if(getField(PedidoCNPJ) == NULL)
					mensagemErro("Cliente não selecionado.");
				else
				{
					goToForm(appPedidos->frmItens);
					salvarDados();
				}
				return true;
		}
	else if(e->eType == popSelectEvent)
		if(controlID == PedidoCidade)
			cidadeSelecionada = codCidades[e->data.popSelect.selection];
	return false;
}

void FrmPedido::doAfterDrawing()
{
	MemHandle hd;
	R_Cidade* cidade;
	Char* pd;
	Char* pn;
	int i;

	cidades = (Char**)MemPtrNew(appPedidos->dbCidade->numeroRegistros() * sizeof(Char*) + 1);
	codCidades = (int*)MemPtrNew(appPedidos->dbCidade->numeroRegistros() * sizeof(int));
	for(i=0; i<appPedidos->dbCidade->numeroRegistros(); i++)
	{
		hd = DmQueryRecord(appPedidos->dbCidade->db, i);
		cidade = (R_Cidade*)MemHandleLock(hd);
		pn = (Char*)MemPtrNew((StrLen(cidade->nome) + 1));
		StrCopy(pn, cidade->nome);
		cidades[i] = pn;
		codCidades[i] = cidade->codigo;
		MemHandleUnlock(hd);
		nCidades += 1;
	}
	LstSetListChoices((ListType*)getControl(PedidoCidadeList), cidades, nCidades);
	if(nCidades >= 10)
		LstSetHeight((ListType*)getControl(PedidoCidadeList), 10);
	else
		LstSetHeight((ListType*)getControl(PedidoCidadeList), nCidades);
	LstDrawList((ListType*)getControl(PedidoCidadeList));

	Form::doAfterDrawing();
}

void FrmPedido::salvarDados()
{
	R_Pedido p;
	bool b;
	int n = appPedidos->dbPedido->ultimoPedido() + 1;

	ErrFatalDisplayIf(getField(PedidoCNPJ) == NULL, "CNPJ do cliente está nulo");
	
	p.n = n;
	StrCopy(p.cnpj, getField(PedidoCNPJ));
	p.status = DIGITANDO;

	b = appPedidos->dbPedido->adicionaRegistro(&p, sizeof(R_Pedido));

	ErrFatalDisplayIf(!b, "Registro do pedido não pode ser adicionado.");

	this->nPedidoAtual = n;
}

void FrmPedido::carregarPreferencias()
{
	PrefPedido* p = (PrefPedido*)appPedidos->preferencias;

	setField(PedidoCNPJ, p->cnpj);
	setField(PedidoCliente, p->fantasia);
	setField(PedidoRazaoSocial, p->razaoSocial);
	this->cidadeSelecionada = p->cidadeSelecionada;
	CtlSetLabel((ControlType*)getControl(PedidoCidade), p->cidadeLista);

	this->carregaPreferencias = false;
}

void FrmPedido::gravarPreferencias()
{
	PrefPedido p;
	Preferencias pref;

	p.numeroForm = N_FORM_PEDIDO;
	if(getField(PedidoCNPJ))
		StrCopy(p.cnpj, getField(PedidoCNPJ));
	else
		StrCopy(p.cnpj, "");
	if(getField(PedidoCliente))
		StrCopy(p.fantasia, getField(PedidoCliente));
	else
		StrCopy(p.fantasia, "");
	if(getField(PedidoRazaoSocial))
		StrCopy(p.razaoSocial, getField(PedidoRazaoSocial));
	else
		StrCopy(p.razaoSocial, "");
	p.cidadeSelecionada = this->cidadeSelecionada;
	if(CtlGetLabel((ControlType*)getControl(PedidoCidade)))
		StrCopy(p.cidadeLista, CtlGetLabel((ControlType*)getControl(PedidoCidade)));
	else
	{
		StrCopy(p.cidadeLista, "Selecione");
		ErrDisplay("Sem cidade para gravar.");
	}
	
	pref.salvar((void*)&p, sizeof(PrefPedido));
}
