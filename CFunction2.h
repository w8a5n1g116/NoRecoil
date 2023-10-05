#pragma once
#include "framework.h"
#include "CWeapon.h"
class CFunction2
{
public:
    static void Move(CWeapon* CurrentWeapon, int isLeftShiftPress, int isCapsLockPress,int scrollLock);
    static void Move2(CWeapon* CurrentWeapon);
    static void FocusMove(CWeapon* CurrentWeapon);
    static void Delay(int timeout_ms);
};

