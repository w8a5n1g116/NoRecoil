#include "CFunction2.h"
#include <chrono>
#include "CWeapon.h"


void CFunction2::Move(CWeapon* CurrentWeapon, int capsLock,int scrollLock)
{

    CurrentWeapon->currentRecoil = capsLock ?  CurrentWeapon->fullAttachmentRecoil : CurrentWeapon->noAttachmentRecoil;
    CurrentWeapon->currentRecoil_2 = CurrentWeapon->currentRecoil;

    int scopeRate = 0;
    switch (CurrentWeapon->scope)
    {
    case 0: 
        scopeRate = CurrentWeapon->scope1X_Scale;
        break;
    case 1:
        scopeRate = CurrentWeapon->scope1_5X_Scale;
        break;
    case 2:
        scopeRate = CurrentWeapon->scope2X_Scale;
        break;
    case 3:
        scopeRate = CurrentWeapon->scope3X_Scale;
        break;
    case 4:
        scopeRate = CurrentWeapon->scope4X_Scale;
        break;
    default:
        break;
    }

    int y = scrollLock ? CurrentWeapon->currentRecoil_2 : CurrentWeapon->currentRecoil  * scopeRate;
    
    mouse_event(MOUSEEVENTF_MOVE, 0,y , 0, 0);
    Delay(CurrentWeapon->interval);
}

void CFunction2::FocusMove(CWeapon* CurrentWeapon)
{
    int y = CurrentWeapon->aimRecoil;
    mouse_event(MOUSEEVENTF_MOVE, 0, y, 0, 0);
    Delay(CurrentWeapon->interval);
}

void CFunction2::Delay(int timeout_ms)
{
    auto start = std::chrono::system_clock::now();
    while (true)
    {
        auto duration =
            std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start).count();
        if (duration > timeout_ms)
        {
            break;
        }
    }
}
