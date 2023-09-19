#pragma once
#include "CAttachment.h"
class CMagazine : public CAttachment
{
public:
	static enum Magazine { SMG, Rifle, Sniper };
	Magazine type;
};

