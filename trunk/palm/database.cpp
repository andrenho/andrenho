#include "database.h"
#include "pedidos.h"

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

bool Database::addRec(Char* reg)
{
	MemHandle h;
	MemPtr p;
	UInt16 idx = DmNumRecords(this->db);

	if(!(h = DmNewRecord(this->db, &idx, StrLen(reg))))
		return false;
	
	p = MemHandleLock(h);
	DmWrite(p, 0, reg, StrLen(reg));
	MemPtrUnlock(p);
	
	DmReleaseRecord(this->db, idx, true);

	return true;
}

bool Database::adicionaRegistro(Registro* r)
{
	Char* c = r->traducao();
	FrmCustomAlert(Debug, c, " ", " ");
	addRec(c);
	MemHandleFree(MemPtrRecoverHandle(c));
}
