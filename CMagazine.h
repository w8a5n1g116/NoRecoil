#pragma once
#include "CAttachment.h"
class CMagazine : public CAttachment
{
public:
	static enum Magazine { SMG,SMG_QUICK, AR,AR_QUICK, SNIPER,SNIPER_QUICK };
	Magazine type;
	int shots = 0;
	CMagazine(Magazine type, int shots);
};

