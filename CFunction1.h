#pragma once
#include "framework.h"
#include "CWeaponLib.h"

class CFunction1
{
public:
	CFunction1();
	static void Move(CWeapon* CurrentWeapon);

	static void Reload(CWeapon* CurrentWeapon);
	static void Delay(int timeout_ms);
};

