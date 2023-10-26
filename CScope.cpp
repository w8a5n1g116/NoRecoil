#include "CScope.h"
#include "GameStart.h"

CScope::CScope(string name, int scope, float y_effect) {
	this->name = name;
	this->scope = scope;
	this->y_effect = y_effect;

	string imageSuffix = "";
	if (GameStart::RESOLUTION_TYPE == 0) {
		imageSuffix = "_1440";
	}
	else if (GameStart::RESOLUTION_TYPE == 1) {
		imageSuffix = "";
	}
	else if (GameStart::RESOLUTION_TYPE == 2) {
		imageSuffix = "_1080";
	}

	templateImage = imread("image/template/" + name + imageSuffix + ".png", IMREAD_COLOR);
	maskImage = imread("image/mask/" + name + imageSuffix + ".png", IMREAD_GRAYSCALE);
}