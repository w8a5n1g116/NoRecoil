#pragma once
#include "CAttachment.h"
class CStock : public CAttachment
{
public:
	static enum Stock { Tactical, BulletLoop, CheekPad, Folding, Heavy};
	Stock type;
	CStock(Stock type, float x_effect);
};

