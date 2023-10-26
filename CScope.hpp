#pragma once
#include "CAttachment.hpp"
class CScope : public  CAttachment
{
public:
	Mat templateImage;
	Mat maskImage;
	int scope = 1;
	CScope() {};
	CScope(string name,int scope ,float y_effect) {
		this->name = name;
		this->scope = scope;
		this->y_effect = y_effect;

		int screenWidth = GetSystemMetrics(SM_CXFULLSCREEN);
		string imageSuffix = "";
		if (screenWidth == 2560) {
			imageSuffix = "_1440";
		}
		else if (screenWidth == 2048) {
			imageSuffix = "";
		}
		else if (screenWidth == 1920) {
			imageSuffix = "_1080";
		}

		templateImage = imread("image/template/" + name + imageSuffix + ".png", IMREAD_COLOR);
		maskImage = imread("image/mask/" + name + imageSuffix + ".png", IMREAD_GRAYSCALE);
	}
};

