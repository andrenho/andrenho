#ifndef DATABASE_H
#define DATABASE_H

#include "palmincludes.h"

#define DB_CREATOR 'WAGN'

class Database
{
public:
	virtual bool adicionaRegistro(void* r, int size);
protected:
	bool openDB();
	void closeDB();
	// MemPtr leRegistro(int n);

	virtual const Char* dbName() =0;
	virtual void populateDB() =0;

	DmOpenRef db;

};

#endif
