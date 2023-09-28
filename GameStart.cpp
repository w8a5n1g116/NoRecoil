#pragma once
#include "GameStart.h"
#include "CFunction1.h"
#include "CFunction2.h"
#include "NoRecoil.h"

extern Mouse_State mouseState;
extern KeyBoard_State keyboardState;

void GameStart::Move()
{
	if (mouseState.isRightButtonPress && mouseState.isLeftButtonPress) {
		if (CurrentWeapon->function == CWeapon::FUNCTION2) {
			CFunction2::Move(CurrentWeapon, keyboardState.capsLock, keyboardState.scrollLock);
		}
		else if (CurrentWeapon->function == CWeapon::FUNCTION1) {
			if (enableTrigger) {
				CFunction2::Move(CurrentWeapon, keyboardState.capsLock, keyboardState.scrollLock);
				enableTrigger = false;
			}
		}
	}
	else if (keyboardState.isLeftContrlPress && mouseState.isLeftButtonPress) {
		CFunction2::FocusMove(CurrentWeapon);
	}

	if (mouseState.isLeftButtonPress == 0) {
		enableTrigger = true;
	}
}

void GameStart::PickWeapon(std::string weaponName)
{
	weaponList[currentPosition -1] = lib.FindWeapon(weaponName);
	CurrentWeapon = weaponList[currentPosition - 1];
}

void GameStart::SwitchWeapon(int position)
{
	currentPosition = position;
	CurrentWeapon = weaponList[currentPosition - 1];
}

void GameStart::LoadSetting()
{
	for (auto& t : lib.weaponMap) {
		t.second.LoadSetting();
	}
}
