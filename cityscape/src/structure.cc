#include "structure.h"

ResidentialInfo* LowResidence3 = new ResidentialInfo(1, 1, 10, 
		ResidentialInfo::LOW, ResidentialInfo::LOW_D, 0x0);
ResidentialInfo* LowResidence2 = new ResidentialInfo(1, 1, 5, 
		ResidentialInfo::LOW, ResidentialInfo::LOW_D, LowResidence3);
ResidentialInfo* LowResidence1 = new ResidentialInfo(1, 1, 2, 
		ResidentialInfo::LOW, ResidentialInfo::LOW_D, LowResidence2);

