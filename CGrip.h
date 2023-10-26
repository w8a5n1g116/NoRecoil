#pragma once
#include "CAttachment.hpp"

class CGrip : public CAttachment
{
public:
	Mat templateImage;
	Mat maskImage;
	CGrip() {};
	CGrip(string name, float y_effect);
};

