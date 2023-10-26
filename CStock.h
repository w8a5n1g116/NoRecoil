#pragma once
#include "CAttachment.hpp"

class CStock : public CAttachment
{
public:
	Mat templateImage;
	Mat maskImage;
	CStock() {};
	CStock(string name, float y_effect);
};

