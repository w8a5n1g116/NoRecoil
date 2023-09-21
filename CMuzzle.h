#pragma once
#include "CAttachment.h"
class CMuzzle : public  CAttachment
{
public:
	static enum Muzzle { SMG_LOWFIRE, SMG_LOWSOUND, SMG_COMP , AR_LOWFIRE, AR_LOWSOUND, AR_COMP, SNIPER_LOWFIRE, SNIPER_LOWSOUND, SNIPER_COMP};
	Muzzle type;
	CMuzzle(Muzzle type, float x_effect);
};

