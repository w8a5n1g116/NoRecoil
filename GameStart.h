#pragma once
#include "CWeaponLib.h"
class GameStart
{
public:
	CWeaponLib lib;
	/*CWeapon* weapon1 = lib.FindWeapon("M416");
	CWeapon* weapon2 = lib.FindWeapon("M416");*/
	CWeapon* weaponList[2] = { 0 };
	CWeapon* CurrentWeapon = nullptr;
	int currentPosition = 1;
	bool enableTrigger = true;

	GameStart() {
		weaponList[0] = lib.FindWeapon("Default");
		weaponList[1] = lib.FindWeapon("Default");
		CurrentWeapon = weaponList[0];
		currentPosition = 1;
	}

	void Move();
	void PickWeapon(std::string weaponName);
	void SwitchWeapon(int position);
	void LoadSetting();
};

