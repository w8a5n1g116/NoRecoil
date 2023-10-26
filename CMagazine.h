#pragma once
#include "CAttachment.hpp"
class CMagazine : public CAttachment
{
public:
	CMagazine() {};
	int shots = 0;
	CMagazine(string name, int shots);
};

