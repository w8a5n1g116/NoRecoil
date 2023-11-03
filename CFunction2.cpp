#include "CFunction2.h"
#include "NoRecoil.h"


extern void SetMessage();
extern HWND hWnd;



void CFunction2::Move(CWeapon* CurrentWeapon, int isLeftAltPress, int scrollLock)
{
    double shot_recoil = 0;
    if (CurrentWeapon->currentShot != CurrentWeapon->shotCount -1) {
        CurrentWeapon->currentShot++;
        shot_recoil = CurrentWeapon->recoilBaseRunning * CurrentWeapon->attachmentEffect * CurrentWeapon->recoilRates[CurrentWeapon->currentShot];
    }
    

    int count = 4;
    for (int i = 0; i < count; i++)
    {
        int offset = 0;
        if (i % 2 == 0) {
            offset = 1;
        }
        else {
            offset = -1;
        }
        mouse_event(MOUSEEVENTF_MOVE, 70, round(shot_recoil / 4), 0, 0);
        Delay(round(CurrentWeapon->shotInterval / 4));
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
