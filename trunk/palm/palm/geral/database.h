#ifndef DATABASE_H
#define DATABASE_H

#include "palmincludes.h"

#define DB_CREATOR 'WGSF'

class Database
{
public:
	~Database();
	virtual bool adicionaRegistro(void* r, int size);
	int numeroRegistros();
	void* registro(int n);

	DmOpenRef db;
protected:
	bool openDB();
	void closeDB();
	// MemPtr leRegistro(int n);

	virtual const Char* dbName() =0;
	virtual void populateDB();
};

#endif
