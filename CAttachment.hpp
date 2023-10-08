#pragma once
#include "framework.h"
class CAttachment
{
public:
	float y_effect = 0;
	string name = "";
	CAttachment(){}
	CAttachment(string name ,float y_effect): name(name), y_effect(y_effect)
	{
		
	}
};

