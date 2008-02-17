#include "database.h"
#include "pedidos.h"

Database::~Database()
{
	closeDB();
}

bool Database::openDB()
{
	LocalID id;
	DmOpenRef db;
	bool first_use = false;

	if(DmCreateDatabase(0, dbName(), DB_CREATOR, 'DATA', false) != dmErrAlreadyExists)
		first_use = true;

	id = DmFindDatabase(0, dbName());
	if(id == 0)
		return false;

	db = DmOpenDatabase(0, id, dmModeReadWrite);
	if(db == 0)
		return false;
	else
	{
		this->db = db;
		if(first_use)
			populateDB();
		return true;
	}
}

void Database::closeDB()
{
	DmCloseDatabase(this->db);
}

bool Database::adicionaRegistro(void* r, int size)
{
	MemHandle h;
	MemPtr p;
	UInt16 idx = DmNumRecords(this->db);

	if(!(h = DmNewRecord(this->db, &idx, size)))
		return false;
	
	p = MemHandleLock(h);
	DmWrite(p, 0, r, size);
	MemPtrUnlock(p);
	
	DmReleaseRecord(this->db, idx, true);

	return true;
}

int Database::numeroRegistros()
{
	return DmNumRecords(this->db);
}

void* Database::registro(int n)
{
	// TODO - testar
	MemPtr p = NULL;
	MemHandle h = DmQueryRecord(this->db, n);
	p = MemHandleLock(h);
	MemHandleUnlock(h);
	return p;
}
