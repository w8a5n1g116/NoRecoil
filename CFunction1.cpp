#include "CFunction1.h"
#include "NoRecoil.h"

extern void SetMessage();
extern HWND hWnd;

CFunction1::CFunction1()
{
}

void CFunction1::Move(CWeapon* CurrentWeapon, int isLeftAltPress, int scrollLock)
{
    double scope_scale = 1;
    if (CurrentWeapon->scope == nullptr) {
        scope_scale = 1;
    }
    else {
        scope_scale = CurrentWeapon->scope->y_effect;
    }

    double shot_recoil = 0;
    if (CurrentWeapon->currentShot != CurrentWeapon->shotCount - 1) {
        CurrentWeapon->currentShot++;
        shot_recoil = CurrentWeapon->recoilBaseRunning * CurrentWeapon->recoilRates[CurrentWeapon->currentShot] * CurrentWeapon->attachmentEffect * scope_scale;
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
        mouse_event(MOUSEEVENTF_MOVE, 0, round(shot_recoil / 4), 0, 0);
        Delay(round(CurrentWeapon->shotInterval / 4));
    }




    SendMessageA(hWnd, WM_CUSTOM_MESSAGE_PICK_WEAPON, 0, 0);
}

void CFunction1::Reload(CWeapon* CurrentWeapon)
{
	CurrentWeapon->currentShot = 0;
}

void CFunction1::Delay(int timeout_ms)
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