#pragma once
#include "framework.h"
#include "CWeapon.h"
class CFunction2
{
public:
    static void Move(CWeapon* CurrentWeapon, int isLeftAltPress,int scrollLock);
    static int MoveTest(int delay);
    static void Move2(CWeapon* CurrentWeapon);
    static void FocusMove(CWeapon* CurrentWeapon);
    static void Delay(int timeout_ms);
};

