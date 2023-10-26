#include "CFunction1.h"
#include <chrono>

CFunction1::CFunction1()
{
}

void CFunction1::Move(CWeapon* CurrentWeapon)
{

	
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