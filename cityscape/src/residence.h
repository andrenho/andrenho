#ifndef RESIDENCE_H
#define RESIDENCE_H

#include "structure.h"

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


class Residence : public Structure
{
public:
	Residence(ResidentialInfo* info) : info(info) { }

	int occupants;
	ResidentialInfo* info;

	virtual bool isResidence() { return true; }
};


extern ResidentialInfo *LowLDResidenceE,
                       *LowHDResidenceE;

#endif
