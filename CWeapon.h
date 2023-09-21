#pragma once
#include "framework.h"
#include "CMuzzle.h"
#include "CStock.h"
#include "CGrip.h"
#include "CMagazine.h"
class CWeapon
{
public:
	string weaponName = "";
	int interval = 0;
	vector<int> offset = {};
	CMuzzle* muzzle = nullptr;
	CGrip* grip = nullptr;
	CMagazine* magazine = nullptr;
	CStock* stock = nullptr;
	int scope =0;
	int currentShot = 0;
	int shotCount = 0;

	CWeapon();

	CWeapon(string weaponName, int interval, vector<int> offset, CMuzzle* muzzle, CGrip* grip, CMagazine* magazine, CStock* stock, int shotCount, int scope);

	CWeapon(string weaponName, int interval, vector<int> offset, int shotCount);

	int ComputeXOffset(int orginOffset);

	void AssembleMuzzle(CMuzzle* muzzle);

	void AssembleGrip(CGrip* grip);

	void AssembleMagazine(CMagazine* magazine);

	void AssembleStock(CStock* stock);

	void AssembleScope(int scope);
};




