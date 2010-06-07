#ifndef STRUCTURE_H
#define STRUCTURE_H

class StructureInfo
{
public:
	StructureInfo(int w, int h) : w(w), h(h) { }
	int w, h;
};


class ResidentialInfo : public StructureInfo
{
public:
	enum Level { LOW, MIDDLE, HIGH, VERYHIGH };
	enum Density { LOW_D, HIGH_D };

	ResidentialInfo(int w, int h, int hh, enum Level level,
			enum Density density, const ResidentialInfo* nextLevel)
		: StructureInfo(w, h), households(hh), level(level),
       		  density(density), nextLevel(nextLevel) { }
	int households;
	enum Level level;
	enum Density density;
	const ResidentialInfo* nextLevel;
};


extern ResidentialInfo* LowResidence1;
extern ResidentialInfo* LowResidence2;
extern ResidentialInfo* LowResidence3;


class Structure
{
public:
	int x, y;
	bool turned;
	StructureInfo* info;
	void* data;

	virtual bool isResidence() { return false; }
};


class Residence : public Structure
{
public:
	int occupants;
	ResidentialInfo* info;

	virtual bool isResidence() { return true; }
};

#endif
