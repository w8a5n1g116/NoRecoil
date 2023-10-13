#pragma once
#include "GameStart.h"
#include "CFunction1.h"
#include "CFunction2.h"
#include "NoRecoil.h"
#include "CWeapon.h"

extern void SetMessage();
extern HWND hWnd;

//默认数据
vector<int> GameStart::DataMatrix = {
		0,0,0,0,0,
		0,0,0,0,0,
		83,77,72,67,63,
		60,56,53,50,48,
		46,44,42,40,39,
		38,36,35,34,33,
		32,31,30,29,28
};

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
	//auto vec = matchWeapon.MatchWeaponName();
	//std::string weaponName = vec[0];	
	//weaponName.erase(weaponName.find_last_not_of("\n") + 1);	//去掉结尾\n	
	//int index = lib.FindWeaponPosition(weaponName);
	//if (index != -1) {
	//	currentIndexPosition = index;
	//	weaponList[0] = lib.FindWeapon(weaponName);
	//	CurrentWeapon = weaponList[0];
	//	SendMessageA(hWnd, WM_CUSTOM_MESSAGE_PICK_WEAPON, currentIndexPosition, 0);
	//}

	//std::string weaponName2 = vec[1];
	//weaponName2.erase(weaponName.find_last_not_of("\n") + 1);	//去掉结尾\n
	//int index2 = lib.FindWeaponPosition(weaponName2);
	//if (index2 != -1) {
	//	currentIndexPosition = index2;
	//	weaponList[1] = lib.FindWeapon(weaponName2);
	//	CurrentWeapon = weaponList[1];
	//	SendMessageA(hWnd, WM_CUSTOM_MESSAGE_PICK_WEAPON, currentIndexPosition, 0);
	//}
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
		currentIndexPosition = maxIndex - 1;
	}
	PickWeapon(lib.weaponNameList[currentIndexPosition]);	
}

void GameStart::Match(Mat* src,int i)
{
	for (auto w : lib.weaponList) {
		bool matched = matchWeapon.MatchWeaponNameImage(src, &w->templateImage, &w->maskImage, weaponNaceRect);	//武器1
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
						int matched = matchWeapon.MatchAttachmentImage(src, &m->templateImage, &m->maskImage, muzzleRect, gripRect, stockRect, scopeRect);
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
						int matched = matchWeapon.MatchAttachmentImage(src, &m->templateImage, &m->maskImage, muzzleRect, gripRect, stockRect, scopeRect);
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
						int matched = matchWeapon.MatchAttachmentImage(src, &m->templateImage, &m->maskImage, muzzleRect, gripRect, stockRect, scopeRect);
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
						int matched = matchWeapon.MatchAttachmentImage(src, &m->templateImage, &m->maskImage, muzzleRect, gripRect, stockRect, scopeRect);
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
			weaponList[i]->ComputeYOffset();
			break;			
		}
	}
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
	LoadDataMatrix();
	LoadKeys();
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
		if(t->weaponName != "Default")
		matchWeapon.SaveMask(t->weaponName);
	}*/

	for (auto t : lib.muzzleList) {
		if (t->name == "Muzzle_None") {
			continue;
		}
		matchWeapon.SaveMask(t->name);
	}

	for (auto t : lib.gripList) {
		if (t->name == "Grip_None") {
			continue;
		}
		matchWeapon.SaveMask(t->name);
	}

	for (auto t : lib.stockList) {
		if (t->name == "Stock_None") {
			continue;
		}
		matchWeapon.SaveMask(t->name);
	}

	for (auto t : lib.scopeList) {
		if (t->name == "Scope_None") {
			continue;
		}
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
	crouchKey = (unsigned short)GetPrivateProfileIntA("Key", "CrouchKey", VK_LSHIFT, iniFilePath.c_str());
	proneKey = (unsigned short)GetPrivateProfileIntA("Key", "ProneKey", VK_CAPITAL, iniFilePath.c_str());
	focusKey = (unsigned short)GetPrivateProfileIntA("Key", "FocusKey", VK_LCONTROL, iniFilePath.c_str());
	holdBreathKey = (unsigned short)GetPrivateProfileIntA("Key", "HoldBreathKey", VK_LMENU, iniFilePath.c_str());
}

void GameStart::SetCrouchKey(unsigned short key)
{
	crouchKey = key;
	WritePrivateProfileStringA("Key", "CrouchKey", std::to_string(key).c_str(), iniFilePath.c_str());
}

void GameStart::SetProneKey(unsigned short key)
{
	proneKey = key;
	WritePrivateProfileStringA("Key", "ProneKey", std::to_string(key).c_str(), iniFilePath.c_str());
}

void GameStart::SetFocusKey(unsigned short key)
{
	focusKey = key;
	WritePrivateProfileStringA("Key", "FocusKey", std::to_string(key).c_str(), iniFilePath.c_str());
}

void GameStart::SetHoldBreathKey(unsigned short key)
{
	holdBreathKey = key;
	WritePrivateProfileStringA("Key", "HoldBreathKey", std::to_string(key).c_str(), iniFilePath.c_str());
}

void CALLBACK GameStart::TimerProc(void* gameStart, BOOLEAN TimerOrWaitFired) {
	((GameStart*)gameStart)->go = false;
}

void CALLBACK GameStart::TimerProc2(void* key, BOOLEAN TimerOrWaitFired) {
	/*mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
	Sleep(function2.interval);
	mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
	mouseState.count++;*/
}

void CALLBACK GameStart::MatchThreadProc(_Inout_ PTP_CALLBACK_INSTANCE Instance, _Inout_opt_ PVOID Context) {
	ThisAndIndex* ti = (ThisAndIndex*)Context;
	ti->_this->Match(ti->image,ti->index);
}

void GameStart::TestDataMatrix() {
	MessageBoxA(hWnd, "点击确定开始测试。", "提示", MB_OK);
	DataMatrix.clear();
	for (int i = 1; i <= 35; i++) {
		int count = 0;
		go = true;
		HANDLE timerHandle;
		CreateTimerQueueTimer(&timerHandle, NULL, TimerProc, this, 1000, 0, WT_EXECUTEINTIMERTHREAD);
		while (go) {
			count += CFunction2::MoveTest(i);
		}
		DataMatrix.push_back(count);
	}

	SaveDataMatrix();
	tested = true;
	//重新读取配置
	LoadSetting();
	MessageBoxA(hWnd, "测试完成", "提示", MB_OK);
}

void GameStart::SaveDataMatrix() {
	for (int i = 1; i <= 35; i++) {
		
		string name = "data_" + to_string(i);
		string value = to_string(DataMatrix[i - 1]);
		if (i < 10) {
			WritePrivateProfileStringA("DataMatrix", name.c_str(), "0", iniFilePath.c_str());
		}
		else {

		}
		WritePrivateProfileStringA("DataMatrix", name.c_str(), value.c_str(), iniFilePath.c_str());
	}
}

void GameStart::LoadDataMatrix() {
	for (int i = 1; i <= 35; i++) {
		string name = "data_" + to_string(i);
		int data = GetPrivateProfileIntA("DataMatrix", name.c_str(), 0, iniFilePath.c_str());
		DataMatrix.push_back(data);
	}

	if (DataMatrix[10] == 0 || tested == false) {
		MessageBoxA(hWnd, "首次运行请在游戏中完成测试操作，具体操作为:\n 1.进入游戏后进入训练场或任意一局游戏.\n2.按下组合键ALT + T一次后等待,请勿多次点击，不然可能会影响测试结果.\n3.等待35s左右，直到提示出现.", "提示", MB_OK);
	}
	else {
		tested = true;
	}
}
