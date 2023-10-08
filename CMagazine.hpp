#pragma once
#include "CAttachment.hpp"
class CMagazine : public CAttachment
{
public:
	int shots = 0;
	CMagazine(string name, int shots)
	{
		this->name = name;
		this->shots = shots;
	}
};

