#pragma once
#include "framework.h"
#include "CWeapon.h"
class CFunction2
{
public:
    static void Move(CWeapon* CurrentWeapon,int capsLock, int scrollLock);
    static void FocusMove(CWeapon* CurrentWeapon);
    static void Delay(int timeout_ms);
};

