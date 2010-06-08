#ifndef STRUCTURE_H
#define STRUCTURE_H

class StructureInfo
{
public:
	StructureInfo(int w, int h) : w(w), h(h) { }
	int w, h;
};


class Structure
{
public:
	int x, y;
	bool turned;
	StructureInfo* info;
	void* data;

	virtual bool isResidence() { return false; }
};

#endif
