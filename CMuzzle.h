#pragma once
#include "CAttachment.hpp"

class CMuzzle : public  CAttachment
{
public:
	Mat templateImage;
	Mat maskImage;
	CMuzzle() {};
	CMuzzle(string name, float y_effect);
};

