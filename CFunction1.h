#pragma once
#include "framework.h"
#include "CWeaponLib.h"
class CFunction1
{
public:
	CWeaponLib lib;
	CWeapon Weapon1 = lib.ACE32;
	CWeapon Weapon2;
	CWeapon* CurrentWeapon = &Weapon1;
	CFunction1();
	void Move();

	void Reload();
	void Delay(int timeout_ms);
};

