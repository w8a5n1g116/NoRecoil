#pragma once
#include "CAttachment.hpp"
class CMuzzle : public  CAttachment
{
public:
	Mat templateImage;
	Mat maskImage;
	CMuzzle(string name, float y_effect) {
		this->name = name;
		this->y_effect = y_effect;
		templateImage = imread("image/template/" + name + ".png", IMREAD_COLOR);
		maskImage = imread("image/mask/" + name + ".png", IMREAD_GRAYSCALE);
	}
};

