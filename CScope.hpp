#pragma once
#include "CAttachment.hpp"
class CScope : public  CAttachment
{
public:
	Mat templateImage;
	Mat maskImage;
	int scope = 1;
	CScope(string name,int scope ,float y_effect) {
		this->name = name;
		this->scope = scope;
		this->y_effect = y_effect;
		templateImage = imread("image/template/" + name + ".png", IMREAD_COLOR);
		maskImage = imread("image/mask/" + name + ".png", IMREAD_GRAYSCALE);
	}
};

