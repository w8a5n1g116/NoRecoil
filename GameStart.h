#pragma once
#include "CWeaponLib.h"
class GameStart
{
public:
	CWeaponLib lib;
	CWeapon* Weapon1 = lib.FindWeapon("M416");
	CWeapon* Weapon2;
	CWeapon* CurrentWeapon = Weapon1;

	void Move( int capsLock, int scrollLock, bool ads, bool aim);
	void SwitchWeapon(std::string weaponName);
	void LoadSetting();
};

