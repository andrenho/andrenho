#ifndef DATABASE_H
#define DATABASE_H

#include "palm.h"

#define DB_CREATOR 'WAGN'

class Registro
{
public:
	virtual Char* traducao() =0;
};

class Database
{
public:
	virtual bool adicionaRegistro(Registro* r);
protected:
	bool openDB();
	void closeDB();
	virtual const Char* dbName() =0;
	virtual void populateDB() =0;
	bool addRec(Char* reg);

	DmOpenRef db;

};

#endif
