#pragma once
#include "GameStart.h"
#include "CFunction1.h"
#include "CFunction2.h"
#include "NoRecoil.h"
#include "CWeapon.h"

extern void SetMessage();
extern HWND hWnd;

CWeaponLib GameStart::WEAPON_LIB = CWeaponLib();
int GameStart::RESOLUTION_TYPE = 0;
int GameStart::SENSITIVE = 50;

GameStart::GameStart() {
	
	InitWeapon();
	//初始化线程池
	InitializeThreadpoolEnvironment(&callbackEnviron);

	
}

void GameStart::InitWeapon() {
	WEAPON_LIB.InitAttachment();
	WEAPON_LIB.InitWeapon();

	weaponList[0] = WEAPON_LIB.FindWeapon("Default");
	weaponList[1] = WEAPON_LIB.FindWeapon("Default");
	CurrentWeapon = weaponList[0];
	currentPosition = 1;
	currentIndexPosition = 0;
	currentIndexPosition1 = 0;
	currentIndexPosition2 = 0;

	LoadSetting();

	SendMessageA(hWnd, WM_CUSTOM_MESSAGE_PICK_WEAPON, currentIndexPosition, 0);
}

void GameStart::LoadResolution()
{
	RESOLUTION_TYPE = GetPrivateProfileIntA("General", "Resolution", VK_LSHIFT, INI_FILE_PATH.c_str());

	SelectResolution(RESOLUTION_TYPE);
}

void GameStart::SelectResolution(int resolution)
{
	RESOLUTION_TYPE = resolution;
	if (RESOLUTION_TYPE == 0) {
		weaponRect1 = p1440WeaponRect1;
		weaponRect2 = p1440WeaponRect2;
		weaponNaceRect = p1440WeaponNameXY;
		muzzleRect = p1440MuzzleXY;
		gripRect = p1440GripXY;
		stockRect = p1440StockXY;
		scopeRect = p1440ScopeXY;
	}
	else if (RESOLUTION_TYPE == 1) {
		weaponRect1 = p1440_125WeaponRect1;
		weaponRect2 = p1440_125WeaponRect2;
		weaponNaceRect = p1440_125WeaponNameXY;
		muzzleRect = p1440_125MuzzleXY;
		gripRect = p1440_125GripXY;
		stockRect = p1440_125StockXY;
		scopeRect = p1440_125ScopeXY;
	}
	else if (RESOLUTION_TYPE == 2) {
		weaponRect1 = p1080WeaponRect1;
		weaponRect2 = p1080WeaponRect2;
		weaponNaceRect = p1080WeaponNameXY;
		muzzleRect = p1080MuzzleXY;
		gripRect = p1080GripXY;
		stockRect = p1080StockXY;
		scopeRect = p1080ScopeXY;
	}

	WritePrivateProfileStringA("General", "Resolution", std::to_string(resolution).c_str(), INI_FILE_PATH.c_str());
}

void GameStart::LoadSensitive() {
	SENSITIVE = GetPrivateProfileIntA("General", "Sensitive", 50, INI_FILE_PATH.c_str());
}

void GameStart::SetSensitive(int sens)
{
	SENSITIVE = sens;
	WritePrivateProfileStringA("General", "Sensitive", std::to_string(SENSITIVE).c_str(), INI_FILE_PATH.c_str());
	CurrentWeapon->SetRecoil();
	SendMessageA(hWnd, WM_CUSTOM_MESSAGE_PICK_WEAPON, currentIndexPosition, 0);
}

void GameStart::Move()
{
	if (mouseState.isRightButtonPress && mouseState.isLeftButtonPress) {
		
		if (CurrentWeapon->function == CWeapon::FUNCTION2) {

			CFunction2::Move(CurrentWeapon, keyboardState.isLeftAltPress, keyboardState.scrollLock);
			
		}
		else if (CurrentWeapon->function == CWeapon::FUNCTION1) {
			if (enableTrigger) {
				CFunction2::Move(CurrentWeapon,0,0);
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
	int index = WEAPON_LIB.FindWeaponPosition(weaponName);
	currentIndexPosition = index;
	weaponList[currentPosition -1] = WEAPON_LIB.FindWeapon(weaponName);
	CurrentWeapon = weaponList[currentPosition - 1];
	SendMessageA(hWnd, WM_CUSTOM_MESSAGE_PICK_WEAPON, currentIndexPosition, 0);
}


void GameStart::PickMatchImageWeapon()
{
	screenShot = matchWeapon.GetScreenShot();
	weapon1Src = screenShot(weaponRect1);
	weapon2Src = screenShot(weaponRect2);

	cvtColor(weapon1Src, weapon1Src, COLOR_RGBA2RGB);
	cvtColor(weapon2Src, weapon2Src, COLOR_RGBA2RGB);

	ti1.image = &weapon1Src;
	ti1.index = 0;
	ti1._this = this;
	ti2.image = &weapon2Src;
	ti2.index = 1;
	ti2._this = this;

	//提交线程池
	TrySubmitThreadpoolCallback(MatchThreadProc, &ti1, &callbackEnviron);
	TrySubmitThreadpoolCallback(MatchThreadProc, &ti2, &callbackEnviron);
	
	CurrentWeapon = weaponList[0];
	SendMessageA(hWnd, WM_CUSTOM_MESSAGE_PICK_WEAPON, currentIndexPosition, 0);
}

void GameStart::PickPreviousWeapon()
{
	if (currentIndexPosition > 0) {
		currentIndexPosition--;
	}else if (currentIndexPosition == 0) {
		currentIndexPosition = WEAPON_LIB.weaponNameList.size() - 1;
	}
	PickWeapon(WEAPON_LIB.weaponNameList[currentIndexPosition]);	
}

void GameStart::Match(Mat* src,int i)
{
	for (auto w : WEAPON_LIB.weaponList) {
		bool matched = matchWeapon.MatchWeaponNameImage(src, &w->templateImage, &w->maskImage, weaponNaceRect);	//武器1
		if (matched) {
			int index = WEAPON_LIB.FindWeaponPosition(w->weaponName);
			if (index != -1) {
				currentIndexPosition = index;
				weaponList[i] = WEAPON_LIB.FindWeapon(w->weaponName);


				bool muzzleMatched = false;
				for (auto m : WEAPON_LIB.muzzleList) {
					if (m->name == "Muzzle_None") {
						continue;
					}
					if (!muzzleMatched) {
						int matched = matchWeapon.MatchAttachmentImage(src, &m->templateImage, &m->maskImage, muzzleRect, gripRect, stockRect, scopeRect);
						if (matched == 1) {
							weaponList[i]->AssembleMuzzle(m);
							muzzleMatched = true;
						}
					}
				}
				if (!muzzleMatched) {
					weaponList[i]->AssembleMuzzle(WEAPON_LIB.FindMuzzle("Muzzle_None"));
				}

				bool gripMatched = false;
				for (auto m : WEAPON_LIB.gripList) {
					if (m->name == "Grip_None") {
						continue;
					}
					if (!gripMatched) {
						int matched = matchWeapon.MatchAttachmentImage(src, &m->templateImage, &m->maskImage, muzzleRect, gripRect, stockRect, scopeRect);
						if (matched == 2) {
							weaponList[i]->AssembleGrip(m);
							gripMatched = true;
						}
					}
				}
				if (!gripMatched) {
					weaponList[i]->AssembleGrip(WEAPON_LIB.FindGrip("Grip_None"));
				}

				bool stockMatched = false;
				for (auto m : WEAPON_LIB.stockList) {
					if (m->name == "Stock_None") {
						continue;
					}
					if (!stockMatched) {
						int matched = matchWeapon.MatchAttachmentImage(src, &m->templateImage, &m->maskImage, muzzleRect, gripRect, stockRect, scopeRect);
						if (matched == 3) {
							weaponList[i]->AssembleStock(m);
							stockMatched = true;
						}
					}
				}
				if (!stockMatched) {
					weaponList[i]->AssembleStock(WEAPON_LIB.FindStock("Stock_None"));
				}

				bool scopeMatched = false;
				for (auto m : WEAPON_LIB.scopeList) {
					if (m->name == "Scope_None") {
						continue;
					}
					if (!scopeMatched) {
						int matched = matchWeapon.MatchAttachmentImage(src, &m->templateImage, &m->maskImage, muzzleRect, gripRect, stockRect, scopeRect);
						if (matched == 4) {
							weaponList[i]->AssembleScope(m);
							scopeMatched = true;
						}
					}
				}
				if (!scopeMatched) {
					CScope* scope = WEAPON_LIB.FindCScope(0);
					weaponList[i]->AssembleScope(scope);
				}


			}
			weaponList[i]->ComputeYOffset();
			SendMessageA(hWnd, WM_CUSTOM_MESSAGE_PICK_WEAPON, currentIndexPosition, 0);
			break;			
		}
	}
}

void GameStart::PickNextWeapon()
{
	if (currentIndexPosition < WEAPON_LIB.weaponNameList.size() - 1) {
		currentIndexPosition++;
	}else if (currentIndexPosition == WEAPON_LIB.weaponNameList.size() - 1) {
		currentIndexPosition = 0;
	}
	PickWeapon(WEAPON_LIB.weaponNameList[currentIndexPosition]);
}

void GameStart::IncrementRecoil()
{
	CurrentWeapon->recoilBase += 1;
	CurrentWeapon->SetRecoil();
	SendMessageA(hWnd, WM_CUSTOM_MESSAGE_PICK_WEAPON, currentIndexPosition, 0);
}

void GameStart::DecrementRecoil()
{
	CurrentWeapon->recoilBase -= 1;
	CurrentWeapon->SetRecoil();
	SendMessageA(hWnd, WM_CUSTOM_MESSAGE_PICK_WEAPON, currentIndexPosition, 0);
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
	LoadKeys();
	LoadResolution();
	LoadSensitive();
	for (auto t : WEAPON_LIB.weaponList) {
		t->LoadSetting();
	}
}

void GameStart::SaveSetting()
{
	for (auto t : WEAPON_LIB.weaponList) {
		t->ChangeSetting();
	}
}

void GameStart::SaveScreenShot()
{
	//matchWeapon.SaveScreenShot(weaponList[0], weaponList[1]);

	/*for (auto t : WEAPON_LIB.weaponList) {
		if(t->weaponName != "Default")
		matchWeapon.SaveMask(t->weaponName);
	}*/

	for (auto t : WEAPON_LIB.muzzleList) {
		if (t->name == "Muzzle_None") {
			continue;
		}
		matchWeapon.SaveMask(t->name);
	}

	for (auto t : WEAPON_LIB.gripList) {
		if (t->name == "Grip_None") {
			continue;
		}
		matchWeapon.SaveMask(t->name);
	}

	for (auto t : WEAPON_LIB.stockList) {
		if (t->name == "Stock_None") {
			continue;
		}
		matchWeapon.SaveMask(t->name);
	}

	for (auto t : WEAPON_LIB.scopeList) {
		if (t->name == "Scope_None") {
			continue;
		}
		matchWeapon.SaveMask(t->name);
	}
}

void GameStart::MoveTest(int y)
{
	CFunction2::MoveTest(y);
	countPx+= y;
}

void GameStart::AssembleMuzzle(string name)
{
	CMuzzle* muzzle = WEAPON_LIB.FindMuzzle(name);
	if (muzzle != nullptr) {
		CurrentWeapon->AssembleMuzzle(muzzle);
	}
}

void GameStart::AssembleGrip(string name)
{
	CGrip* grip = WEAPON_LIB.FindGrip(name);
	if (grip != nullptr) {
		CurrentWeapon->AssembleGrip(grip);
	}
}

void GameStart::AssembleMagazine(string name)
{
}

void GameStart::AssembleStock(string name)
{
	CStock* stock = WEAPON_LIB.FindStock(name);
	if (stock != nullptr) {
		CurrentWeapon->AssembleStock(stock);
	}
}

void GameStart::AssembleScope(int scope_type)
{
	CScope* scope = WEAPON_LIB.FindCScope(scope_type);
	if (scope != nullptr) {
		CurrentWeapon->AssembleScope(scope);
	}
}

void GameStart::DoKeyBoardEvent(unsigned short key, int keyDownOrUp)
{
	if (key == crouchKey) {
		if (keyDownOrUp == 1) {
			isCrouch = true;			
			if (!isProne) {
				CurrentWeapon->Crouch(isCrouch);
			}
		}
		else {
			isCrouch = false;
			if (!isProne) {
				CurrentWeapon->Crouch(isCrouch);
			}
		}
	}
	else if (key == proneKey) {
		if (keyDownOrUp == 1) {
			isProne = true;
			if (!isCrouch) {
				CurrentWeapon->Prone(isProne);
			}

		}
		else {			
			isProne = false;
			if (!isCrouch) {
				CurrentWeapon->Prone(isProne);
			}
		}
	}
	else if (key == focusKey) {
		if (keyDownOrUp == 1) {

		}
		else {

		}
	}
	else if (key == holdBreathKey) {
		if (keyDownOrUp == 1) {

		}
		else {

		}
	}

	SetMessage();
}

void GameStart::LoadKeys()
{
	crouchKey = (unsigned short)GetPrivateProfileIntA("Key", "CrouchKey", VK_LSHIFT, INI_FILE_PATH.c_str());
	proneKey = (unsigned short)GetPrivateProfileIntA("Key", "ProneKey", VK_CAPITAL, INI_FILE_PATH.c_str());
	focusKey = (unsigned short)GetPrivateProfileIntA("Key", "FocusKey", VK_LCONTROL, INI_FILE_PATH.c_str());
	holdBreathKey = (unsigned short)GetPrivateProfileIntA("Key", "HoldBreathKey", VK_LMENU, INI_FILE_PATH.c_str());
}

void GameStart::SetCrouchKey(unsigned short key)
{
	crouchKey = key;
	WritePrivateProfileStringA("Key", "CrouchKey", std::to_string(key).c_str(), INI_FILE_PATH.c_str());
}

void GameStart::Reload()
{
	CurrentWeapon->Reload();
}

void GameStart::SetProneKey(unsigned short key)
{
	proneKey = key;
	WritePrivateProfileStringA("Key", "ProneKey", std::to_string(key).c_str(), INI_FILE_PATH.c_str());
}

void GameStart::SetFocusKey(unsigned short key)
{
	focusKey = key;
	WritePrivateProfileStringA("Key", "FocusKey", std::to_string(key).c_str(), INI_FILE_PATH.c_str());
}

void GameStart::SetHoldBreathKey(unsigned short key)
{
	holdBreathKey = key;
	WritePrivateProfileStringA("Key", "HoldBreathKey", std::to_string(key).c_str(), INI_FILE_PATH.c_str());
}


void CALLBACK GameStart::TimerProc(void* gameStart, BOOLEAN TimerOrWaitFired) {
	((GameStart*)gameStart)->go = false;
}

void CALLBACK GameStart::TimerProc2(void* key, BOOLEAN TimerOrWaitFired) {
	
}

void CALLBACK GameStart::MatchThreadProc(_Inout_ PTP_CALLBACK_INSTANCE Instance, _Inout_opt_ PVOID Context) {
	ThisAndIndex* ti = (ThisAndIndex*)Context;
	ti->_this->Match(ti->image,ti->index);
}
