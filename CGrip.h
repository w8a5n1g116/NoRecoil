#pragma once
#include "CAttachment.h"
class CGrip : public CAttachment
{
public:
	static enum Grip { Angled, Half, Laser, LightWeight, Thumb, Vertical };
	Grip type;
};

