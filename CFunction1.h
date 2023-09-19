#pragma once
#include "framework.h"
#include "CWeapon.h"
class CFunction1
{
	CWeapon Weapon1;
	CWeapon Weapon2;
	CWeapon* CurrentWeapon;
	void Move();
};

