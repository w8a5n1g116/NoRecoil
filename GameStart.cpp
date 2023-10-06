#pragma once
#include "GameStart.h"
#include "CFunction1.h"
#include "CFunction2.h"
#include "NoRecoil.h"

extern Mouse_State mouseState;
extern KeyBoard_State keyboardState;
extern HWND hWnd;

void GameStart::Move()
{
	if (mouseState.isRightButtonPress && mouseState.isLeftButtonPress) {
		
		if (CurrentWeapon->function == CWeapon::FUNCTION2) {
			//CreateTimerQueueTimer(&m_timerHandle, NULL, this->TimerProc, (void*)this, 1000, 0, WT_EXECUTEINTIMERTHREAD);
			//if (go) {
				CFunction2::Move(CurrentWeapon, keyboardState.isLeftAltPress, keyboardState.scrollLock);
			//}
			
		}
		else if (CurrentWeapon->function == CWeapon::FUNCTION1) {
			if (enableTrigger) {
				CFunction2::Move2(CurrentWeapon);
				enableTrigger = false;
			}
		}
	}
	else if (keyboardState.isLeftContrlPress && mouseState.isLeftButtonPress) {
		CFunction2::FocusMove(CurrentWeapon);
	}

	if (mouseState.isLeftButtonPress == 0) {
		enableTrigger = true;
		//go = true;
	}
}

void GameStart::PickWeapon(std::string weaponName)
{
	int index = lib.FindWeaponPosition(weaponName);
	currentIndexPosition = index;
	weaponList[currentPosition -1] = lib.FindWeapon(weaponName);
	CurrentWeapon = weaponList[currentPosition - 1];
	SendMessageA(hWnd, WM_CUSTOM_MESSAGE_PICK_WEAPON, currentIndexPosition, 0);
}

void GameStart::PickFirstWeapon()
{
	std::string weaponName = matchWeapon.MatchFirstWeapon();
	weaponName.erase(weaponName.find_last_not_of("\n") + 1);	//去掉结尾\n
	int index = lib.FindWeaponPosition(weaponName);
	if (index != -1) {
		currentIndexPosition = index;
		weaponList[0] = lib.FindWeapon(weaponName);
		CurrentWeapon = weaponList[0];
		SendMessageA(hWnd, WM_CUSTOM_MESSAGE_PICK_WEAPON, currentIndexPosition, 0);
	}
	
}

void GameStart::PickSecondWeapon()
{
	std::string weaponName = matchWeapon.MatchSecondWeapon();
	weaponName.erase(weaponName.find_last_not_of("\n") + 1);	//去掉结尾\n
	int index = lib.FindWeaponPosition(weaponName);
	if (index != -1) {
		currentIndexPosition = index;
		weaponList[1] = lib.FindWeapon(weaponName);
		CurrentWeapon = weaponList[1];
		SendMessageA(hWnd, WM_CUSTOM_MESSAGE_PICK_WEAPON, currentIndexPosition, 0);
	}
}

void GameStart::PickPreviousWeapon()
{
	if (currentIndexPosition > 0) {
		currentIndexPosition--;
	}else if (currentIndexPosition == 0) {
		currentIndexPosition = maxIndex - 1;
	}
	PickWeapon(lib.weaponNameList[currentIndexPosition]);	
}

void GameStart::PickNextWeapon()
{
	if (currentIndexPosition < maxIndex - 1) {
		currentIndexPosition++;
	}else if (currentIndexPosition == maxIndex - 1) {
		currentIndexPosition = 0;
	}
	PickWeapon(lib.weaponNameList[currentIndexPosition]);
}

void GameStart::IncrementRecoil()
{
	CurrentWeapon->SetParameter(CurrentWeapon->recoilStand + 1);
}

void GameStart::DecrementRecoil()
{
	CurrentWeapon->SetParameter(CurrentWeapon->recoilStand - 1);
}

void GameStart::SwitchWeapon(int position)
{
	if (currentPosition == 1) {
		currentIndexPosition1 = currentIndexPosition;
	}
	else if (currentPosition == 2) {
		currentIndexPosition2 = currentIndexPosition;
	}

	if (position == 1) {
		currentIndexPosition = currentIndexPosition1;
	}
	else if (position == 2) {
		currentIndexPosition = currentIndexPosition2;
	}
	currentPosition = position;
	CurrentWeapon = weaponList[currentPosition - 1];
	
	SendMessageA(hWnd, WM_CUSTOM_MESSAGE_PICK_WEAPON, currentIndexPosition, 0);
}

void GameStart::LoadSetting()
{
	for (auto& t : lib.weaponList) {
		t.LoadSetting();
	}
}

void GameStart::SaveSetting()
{
	for (auto& t : lib.weaponList) {
		t.ChangeSetting();
	}
}

void GameStart::MatchWeapon()
{
	PickSecondWeapon();
	PickFirstWeapon();
}

void CALLBACK GameStart::TimerProc(void* gameStart, BOOLEAN TimerOrWaitFired) {
	((GameStart*)gameStart)->go = false;
}
