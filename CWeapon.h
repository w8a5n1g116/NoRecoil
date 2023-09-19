#pragma once
#include "framework.h"
#include "CMuzzle.h"
#include "CStock.h"
#include "CGrip.h"
#include "CMagazine.h"
class CWeapon
{
public:
	string weaponName;
	int interval;
	vector<int> offset;	
	CMuzzle* muzzle;
	CGrip* grip;
	CMagazine* magazine;
	CStock* stock;
	int scope;

	CWeapon(string weaponName, int interval, vector<int> offset, CMuzzle* muzzle, CGrip* grip, CMagazine* magazine, CStock* stock, int scope);

	int ComputeXOffset(int orginOffset);
};




