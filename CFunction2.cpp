#include "CFunction2.h"
#include "CWeapon.h"
#include "NoRecoil.h"


extern void SetMessage();
extern HWND hWnd;



void CFunction2::Move(CWeapon* CurrentWeapon, int isLeftAltPress, int scrollLock)
{
    double shot_recoil = CurrentWeapon->recoilBase *  CurrentWeapon->recoilRates[CurrentWeapon->currentShot];

    int count = 3;
    for (int i = 0; i < count; i++)
    {
        mouse_event(MOUSEEVENTF_MOVE, 0, shot_recoil / 3, 0, 0);
        Delay(CurrentWeapon->shotInterval / 3);
    }


    CurrentWeapon->currentShot++;
    if (CurrentWeapon->currentShot == CurrentWeapon->shotCount) {
        CurrentWeapon->currentShot = 0;
    } 
    SendMessageA(hWnd, WM_CUSTOM_MESSAGE_PICK_WEAPON, 0, 0);
}


void CFunction2::MoveTest(int y)
{
    mouse_event(MOUSEEVENTF_MOVE, 0, y, 0, 0);
}


void CFunction2::FocusMove(CWeapon* CurrentWeapon)
{
    int y = CurrentWeapon->aimRecoil;
    mouse_event(MOUSEEVENTF_MOVE, 0, y, 0, 0);
    Delay(CurrentWeapon->shotInterval);
}

void CFunction2::Delay(int timeout_ms)
{
    auto start = chrono::system_clock::now();
    while (true)
    {
        auto duration =
            chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now() - start).count();
        if (duration > timeout_ms)
        {
            break;
        }
    }
}
