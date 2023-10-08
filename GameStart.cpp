#pragma once
#include "GameStart.h"
#include "CFunction1.h"
#include "CFunction2.h"
#include "NoRecoil.h"
#include "CWeapon.h"

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

void GameStart::PickMatchWeapon()
{
	auto vec = matchWeapon.MatchWeaponName();
	std::string weaponName = vec[0];	
	weaponName.erase(weaponName.find_last_not_of("\n") + 1);	//去掉结尾\n	
	int index = lib.FindWeaponPosition(weaponName);
	if (index != -1) {
		currentIndexPosition = index;
		weaponList[0] = lib.FindWeapon(weaponName);
		CurrentWeapon = weaponList[0];
		SendMessageA(hWnd, WM_CUSTOM_MESSAGE_PICK_WEAPON, currentIndexPosition, 0);
	}

	std::string weaponName2 = vec[1];
	weaponName2.erase(weaponName.find_last_not_of("\n") + 1);	//去掉结尾\n
	int index2 = lib.FindWeaponPosition(weaponName2);
	if (index2 != -1) {
		currentIndexPosition = index2;
		weaponList[1] = lib.FindWeapon(weaponName2);
		CurrentWeapon = weaponList[1];
		SendMessageA(hWnd, WM_CUSTOM_MESSAGE_PICK_WEAPON, currentIndexPosition, 0);
	}
}

void GameStart::PickMatchImageWeapon()
{
	Mat screenshot = matchWeapon.GetScreenShot();
	Mat weapon1Src = screenshot(Rect(1772, 120, 648, 255));
	Mat weapon2Src = screenshot(Rect(1772, 394, 648, 255));
	bool weapon1Matched = false;
	bool weapon2Matched = false;
	for (auto w : lib.weaponList) {
		if (!weapon1Matched || !weapon2Matched) {

			for (int i = 1; i >=0; i--) {
				Mat src;
				if (i == 0) {
					src = weapon1Src;
				}
				else {
					src = weapon2Src;
				}
				bool matched = matchWeapon.MatchWeaponNameImage(src, w->templateImage, w->maskImage);	//武器1
				if (matched) {
					int index = lib.FindWeaponPosition(w->weaponName);
					if (index != -1) {
						currentIndexPosition = index;
						weaponList[i] = lib.FindWeapon(w->weaponName);


						bool muzzleMatched = false;
						for (auto m : lib.muzzleList) {
							if (m->name == "Muzzle_None") {
								continue;
							}
							if (!muzzleMatched) {
								int matched = matchWeapon.MatchAttachmentImage(src, m->templateImage, m->maskImage);
								if (matched == 1) {
									weaponList[i]->AssembleMuzzle(m);
									muzzleMatched = true;
								}
							}
						}
						if (!muzzleMatched) {
							weaponList[i]->AssembleMuzzle(lib.FindMuzzle("Muzzle_None"));
						}

						bool gripMatched = false;
						for (auto m : lib.gripList) {
							if (m->name == "Grip_None") {
								continue;
							}
							if (!gripMatched) {
								int matched = matchWeapon.MatchAttachmentImage(src, m->templateImage, m->maskImage);
								if (matched == 2) {
									weaponList[i]->AssembleGrip(m);
									gripMatched = true;
								}
							}
						}
						if (!gripMatched) {
							weaponList[i]->AssembleGrip(lib.FindGrip("Grip_None"));
						}

						bool stockMatched = false;
						for (auto m : lib.stockList) {
							if (m->name == "Stock_None") {
								continue;
							}
							if (!stockMatched) {
								int matched = matchWeapon.MatchAttachmentImage(src, m->templateImage, m->maskImage);
								if (matched == 3) {
									weaponList[i]->AssembleStock(m);
									stockMatched = true;
								}
							}
						}
						if (!stockMatched) {
							weaponList[i]->AssembleStock(lib.FindStock("Stock_None"));
						}

						bool scopeMatched = false;
						for (auto m : lib.scopeList) {
							if (m->name == "Scope_None") {
								continue;
							}
							if (!scopeMatched) {
								int matched = matchWeapon.MatchAttachmentImage(src, m->templateImage, m->maskImage);
								if (matched == 4) {
									weaponList[i]->AssembleScope(m->scope, m);
									scopeMatched = true;
								}
							}
						}
						if (!scopeMatched) {
							CScope* scope = lib.FindCScope(0);
							weaponList[i]->AssembleScope(scope->scope, scope);
						}

						
					}
					if (i == 0) {
						weapon1Matched = true;
					}
					else {
						weapon2Matched = true;
					}
					
					weaponList[i]->ComputeYOffset();
				}

			
			}
		}	
	}
	CurrentWeapon = weaponList[0];
	SendMessageA(hWnd, WM_CUSTOM_MESSAGE_PICK_WEAPON, currentIndexPosition, 0);
	
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
	for (auto t : lib.weaponList) {
		t->LoadSetting();
	}
}

void GameStart::SaveSetting()
{
	for (auto t : lib.weaponList) {
		t->ChangeSetting();
	}
}

void GameStart::SaveScreenShot()
{
	//matchWeapon.SaveScreenShot(weaponList[0], weaponList[1]);

	/*for (auto t : lib.weaponList) {
		if(t.weaponName != "Default")
		matchWeapon.SaveMask(t.weaponName);
	}*/

	for (auto t : lib.muzzleList) {
		matchWeapon.SaveMask(t->name);
	}

	for (auto t : lib.gripList) {
		matchWeapon.SaveMask(t->name);
	}

	for (auto t : lib.stockList) {
		matchWeapon.SaveMask(t->name);
	}

	for (auto t : lib.scopeList) {
		matchWeapon.SaveMask(t->name);
	}
}

void GameStart::AssembleMuzzle(string name)
{
	CMuzzle* muzzle = lib.FindMuzzle(name);
	if (muzzle != nullptr) {
		CurrentWeapon->AssembleMuzzle(muzzle);
	}
}

void GameStart::AssembleGrip(string name)
{
	CGrip* grip = lib.FindGrip(name);
	if (grip != nullptr) {
		CurrentWeapon->AssembleGrip(grip);
	}
}

void GameStart::AssembleMagazine(string name)
{
}

void GameStart::AssembleStock(string name)
{
	CStock* stock = lib.FindStock(name);
	if (stock != nullptr) {
		CurrentWeapon->AssembleStock(stock);
	}
}

void GameStart::AssembleScope(int scope)
{
	CScope* cscope = lib.FindCScope(scope);
	if (cscope != nullptr) {
		CurrentWeapon->AssembleScope(cscope->scope, cscope);
	}
}

void CALLBACK GameStart::TimerProc(void* gameStart, BOOLEAN TimerOrWaitFired) {
	((GameStart*)gameStart)->go = false;
}
