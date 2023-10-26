#pragma once
#include "CAttachment.hpp"
class CScope : public  CAttachment
{
public:
	Mat templateImage;
	Mat maskImage;
	int scope = 1;
	CScope() {};
	CScope(string name, int scope, float y_effect);
};

