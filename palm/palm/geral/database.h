#ifndef DATABASE_H
#define DATABASE_H

#include "palmincludes.h"
#include "segment.h"

#define DB_CREATOR 'WGSF'

class Database
{
public:
	~Database() GERAL;
	virtual bool adicionaRegistro(void* r, int size) GERAL;
	int numeroRegistros() GERAL;
	void* registro(int n) GERAL;

	DmOpenRef db;
protected:
	bool openDB() GERAL;
	void closeDB() GERAL;
	// MemPtr leRegistro(int n);

	virtual const Char* dbName() =0;
	virtual void populateDB() GERAL;
};

#endif
