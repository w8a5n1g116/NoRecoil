#include "GameStart.h"
#include "CFunction1.h"
#include "CFunction2.h"

void GameStart::Move( int capsLock, int scrollLock,bool ads, bool aim)
{
	if (ads) {
		if (CurrentWeapon->function == CWeapon::FUNCTION2) {
			CFunction2::Move(CurrentWeapon, capsLock, scrollLock);
		}
		else if (CurrentWeapon->function == CWeapon::FUNCTION1) {
			CFunction1::Move(CurrentWeapon);
		}
	}
	else if (aim) {
		CFunction2::FocusMove(CurrentWeapon);
	}
}

void GameStart::SwitchWeapon(std::string weaponName)
{
	CurrentWeapon = lib.FindWeapon(weaponName);
}

void GameStart::LoadSetting()
{
	for (auto& t : lib.weaponMap) {
		t.second.LoadSetting();
	}
}
