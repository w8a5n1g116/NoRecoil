#include "CFunction1.h"
#include <chrono>

CFunction1::CFunction1()
{
}

void CFunction1::Move(CWeapon* CurrentWeapon)
{
	int count = 10;
	int x = 0;
	float sensitive = 1;
	for (int i = 0; i < count; i++)
	{
		mouse_event(MOUSEEVENTF_MOVE, x, CurrentWeapon->ComputeXOffset(CurrentWeapon->offset[CurrentWeapon->currentShot] / count * sensitive), 0, 0);
		//Sleep(CurrentWeapon->interval);
		Delay(CurrentWeapon->interval / count);
	}
	
	
	CurrentWeapon->currentShot++;
	if (CurrentWeapon->currentShot == CurrentWeapon->shotCount) {
		CurrentWeapon->currentShot = 0;
	}
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