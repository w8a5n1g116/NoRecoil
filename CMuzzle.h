#pragma once
#include "CAttachment.h"
class CMuzzle : public  CAttachment
{
public:
	static enum Muzzle { SMG, Rifle, Sniper };
	Muzzle type;
};

