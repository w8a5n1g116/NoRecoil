#include "CFunction2.h"
#include "CWeapon.h"
#include "NoRecoil.h"


extern void SetMessage();
extern HWND hWnd;


void CFunction2::Move(CWeapon* CurrentWeapon, int isLeftAltPress,int scrollLock)
{

    CurrentWeapon->currentRecoil =  CurrentWeapon->moveY;
    CurrentWeapon->currentRecoil_2 = CurrentWeapon->currentRecoil;

    float scopeRate = 0;
    switch (CurrentWeapon->scope)
    {
    case 0:
        scopeRate = CurrentWeapon->scope1X_Scale;
        break;
    case 1: 
        scopeRate = CurrentWeapon->scope1X_Scale;
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
    case 6:
        scopeRate = CurrentWeapon->scope6X_Scale;
        break;
    case 8:
        scopeRate = CurrentWeapon->scope8X_Scale;
        break;
    case 5:
        scopeRate = CurrentWeapon->scope1_5X_Scale;
        break;
    default:
        break;
    }

    

    int y = scrollLock ? CurrentWeapon->currentRecoil_2 : CurrentWeapon->currentRecoil  * scopeRate;

    mouse_event(MOUSEEVENTF_MOVE, 0, y, 0, 0);
    Delay(CurrentWeapon->interval);

}

void CFunction2::Move3(CWeapon* CurrentWeapon, int isLeftAltPress, int scrollLock)
{
    float shot_recoil = CurrentWeapon->recoilBase *  CurrentWeapon->recoilRates[CurrentWeapon->currentShot];

    //std::vector<int> retVec = CWeapon::findMatch(shot_recoil);

    //CurrentWeapon->currentRecoil = retVec[1];



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

int CFunction2::MoveTest(int delay)
{
    mouse_event(MOUSEEVENTF_MOVE, 0, 1, 0, 0);
    Delay(delay);
    return 1;
}

void CFunction2::MoveTest(int y,int x)
{
    mouse_event(MOUSEEVENTF_MOVE, 0, y, 0, 0);
}

void CFunction2::Move2(CWeapon* CurrentWeapon)
{
    float scopeRate = 0;
    switch (CurrentWeapon->scope)
    {
    case 0:
        scopeRate = CurrentWeapon->scope1X_Scale;
        break;
    case 1:
        scopeRate = CurrentWeapon->scope1X_Scale;
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
    case 6:
        scopeRate = CurrentWeapon->scope6X_Scale;
        break;
    case 8:
        scopeRate = CurrentWeapon->scope8X_Scale;
        break;
    case 5:
        scopeRate = CurrentWeapon->scope1_5X_Scale;
        break;
    default:
        break;
    }

    CurrentWeapon->currentRecoil = CurrentWeapon->recoil;
    int y =  CurrentWeapon->currentRecoil * scopeRate;
    mouse_event(MOUSEEVENTF_MOVE, 0, y, 0, 0);
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
