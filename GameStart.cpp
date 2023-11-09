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
int GameStart::SWITCH_ADS = 0;
int GameStart::SWITCH_CROUCH = 0;
int GameStart::SWITCH_PRONE = 0;

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
		tabOpenBGRect = p1440TabOpenRect;
		stanceBGRect = p1440StanceRect;
		tabOpenRect = p1440TabOpenXY;
		stanceRect = p1440StanceXY;
		adsRect = p1440adsXY;
		adsBGRect = p1440adsRect;

		stanceMatchCrouchImage = imread("image/template/crouch_1440.png", IMREAD_COLOR);
		stanceMatchCrouchImageMask = imread("image/mask/crouch_1440.png", IMREAD_GRAYSCALE);

		stanceMatchProneImage = imread("image/template/prone_1440.png", IMREAD_COLOR);
		stanceMatchProneImageMask = imread("image/mask/prone_1440.png", IMREAD_GRAYSCALE);

		tabOpenMatchImage = imread("image/template/tab_open_1440.png", IMREAD_COLOR);
		tabOpenMatchImageMask = imread("image/mask/tab_open_1440.png", IMREAD_GRAYSCALE);

		adsMatchImage = imread("image/template/ads_1440.png", IMREAD_COLOR);
		adsMatchImageMask = imread("image/mask/ads_1440.png", IMREAD_GRAYSCALE);
	}
	else if (RESOLUTION_TYPE == 1) {
		weaponRect1 = p1440_125WeaponRect1;
		weaponRect2 = p1440_125WeaponRect2;
		weaponNaceRect = p1440_125WeaponNameXY;
		muzzleRect = p1440_125MuzzleXY;
		gripRect = p1440_125GripXY;
		stockRect = p1440_125StockXY;
		scopeRect = p1440_125ScopeXY;
		tabOpenBGRect = p1440_125TabOpenRect;
		stanceBGRect = p1440_125StanceRect;
		tabOpenRect = p1440_125TabOpenXY;
		stanceRect = p1440_125StanceXY;
		adsRect = p1440_125adsXY;
		adsBGRect = p1440_125adsRect;

		stanceMatchCrouchImage = imread("image/template/crouch.png", IMREAD_COLOR);
		stanceMatchCrouchImageMask = imread("image/mask/crouch.png", IMREAD_GRAYSCALE);

		stanceMatchProneImage = imread("image/template/prone.png", IMREAD_COLOR);
		stanceMatchProneImageMask = imread("image/mask/prone.png", IMREAD_GRAYSCALE);

		tabOpenMatchImage = imread("image/template/tab_open.png", IMREAD_COLOR);
		tabOpenMatchImageMask = imread("image/mask/tab_open.png", IMREAD_GRAYSCALE);

		adsMatchImage = imread("image/template/ads.png", IMREAD_COLOR);
		adsMatchImageMask = imread("image/mask/ads.png", IMREAD_GRAYSCALE);
	}
	else if (RESOLUTION_TYPE == 2) {
		weaponRect1 = p1080WeaponRect1;
		weaponRect2 = p1080WeaponRect2;
		weaponNaceRect = p1080WeaponNameXY;
		muzzleRect = p1080MuzzleXY;
		gripRect = p1080GripXY;
		stockRect = p1080StockXY;
		scopeRect = p1080ScopeXY;
		tabOpenBGRect = p1080TabOpenRect;
		stanceBGRect = p1080StanceRect;
		tabOpenRect = p1080TabOpenXY;
		stanceRect = p1080StanceXY;
		adsRect = p1080adsXY;
		adsBGRect = p1080adsRect;

		stanceMatchCrouchImage = imread("image/template/crouch_1080.png", IMREAD_COLOR);
		stanceMatchCrouchImageMask = imread("image/mask/crouch_1080.png", IMREAD_GRAYSCALE);

		stanceMatchProneImage = imread("image/template/prone_1080.png", IMREAD_COLOR);
		stanceMatchProneImageMask = imread("image/mask/prone_1080.png", IMREAD_GRAYSCALE);

		tabOpenMatchImage = imread("image/template/tab_open_1080.png", IMREAD_COLOR);
		tabOpenMatchImageMask = imread("image/mask/tab_open_1080.png", IMREAD_GRAYSCALE);

		adsMatchImage = imread("image/template/ads_1080.png", IMREAD_COLOR);
		adsMatchImageMask = imread("image/mask/ads_1080.png", IMREAD_GRAYSCALE);
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
	if (SWITCH_ADS == 0) {
		if (mouseState.isRightButtonPress && mouseState.isLeftButtonPress) {

			if (CurrentWeapon->function == CWeapon::FUNCTION2) {

				CFunction2::Move(this, keyboardState.isLeftAltPress, keyboardState.scrollLock);

			}
			else if (CurrentWeapon->function == CWeapon::FUNCTION1) {
				if (enableTrigger) {
					CFunction2::Move(this, 0, 0);
					enableTrigger = false;
				}
			}
		}
		else if (keyboardState.isLeftContrlPress && mouseState.isLeftButtonPress) {
			//只有当背包没有打开时才腰射，不然仍东西按ctrl鼠标会下移
			if (!packageOpened) {
				CFunction2::FocusMove(CurrentWeapon);
			}	
		}

		if (mouseState.isLeftButtonPress == 0) {
			enableTrigger = true;
			//松开鼠标左键后座index自动归零，保证下次开枪后坐力后坐力正常
			CurrentWeapon->currentShot = 0;
		}
	}
	else {	//切换开镜
		if (adsOpened) {
			if (mouseState.isLeftButtonPress) {

				if (CurrentWeapon->function == CWeapon::FUNCTION2) {

					CFunction2::Move(this, keyboardState.isLeftAltPress, keyboardState.scrollLock);

				}
				else if (CurrentWeapon->function == CWeapon::FUNCTION1) {
					if (enableTrigger) {
						CFunction2::Move(this, 0, 0);
						enableTrigger = false;
					}
				}
			}
			else if (keyboardState.isLeftContrlPress && mouseState.isLeftButtonPress) {
				if (!packageOpened) {
					CFunction2::FocusMove(CurrentWeapon);
				}
			}
			if (mouseState.isLeftButtonPress == 0) {
				enableTrigger = true;
				//松开鼠标左键后座index自动归零，保证下次开枪后坐力后坐力正常
				CurrentWeapon->currentShot = 0;
			}
		}
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


void GameStart::CanDoMatchWeapon() {
	screenShot = matchWeapon.GetScreenShot();
	tabOpenSrc = screenShot(tabOpenBGRect);

	cvtColor(tabOpenSrc, tabOpenSrc, COLOR_RGBA2RGB);

	tiTabOpen.image = &tabOpenSrc;
	tiTabOpen._this = this;

	 bool ret = TrySubmitThreadpoolCallback(CanMatchWeaponThreadProc, &tiTabOpen, &callbackEnviron);
}

void GameStart::DoMatchStance()
{
	screenShot = matchWeapon.GetScreenShot();
	stanceSrc = screenShot(stanceBGRect);

	cvtColor(stanceSrc, stanceSrc, COLOR_RGBA2RGB);

	tiStance.image = &stanceSrc;
	tiStance._this = this;

	bool ret = TrySubmitThreadpoolCallback(StanceMatchThreadProc, &tiStance, &callbackEnviron);
}

void GameStart::DoMatchAdsOpen()
{
	screenShot = matchWeapon.GetScreenShot();

	adsSrc = screenShot(adsBGRect);

	cvtColor(adsSrc, adsSrc, COLOR_RGBA2RGB);
	
	tiAds.image = &adsSrc;
	tiAds._this = this;

	bool ret = TrySubmitThreadpoolCallback(AdsMatchThreadProc, &tiAds, &callbackEnviron);
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
	bool ret1 = TrySubmitThreadpoolCallback(WeaponMatchThreadProc, &ti1, &callbackEnviron);
	bool ret2 = TrySubmitThreadpoolCallback(WeaponMatchThreadProc, &ti2, &callbackEnviron);
	
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

				//提交线程池
				if (i == 0) {
					tiMuzzle1.image = src;
					tiMuzzle1.index = 0;
					tiMuzzle1._this = this;
					tiGrip1.image = src;
					tiGrip1.index = 0;
					tiGrip1._this = this;
					tiStock1.image = src;
					tiStock1.index = 0;
					tiStock1._this = this;
					tiScope1.image = src;
					tiScope1.index = 0;
					tiScope1._this = this;
					bool ret1 = TrySubmitThreadpoolCallback(MuzzleMatchThreadProc, &tiMuzzle1, &callbackEnviron);
					bool ret2 = TrySubmitThreadpoolCallback(GripMatchThreadProc, &tiGrip1, &callbackEnviron);
					bool ret3 = TrySubmitThreadpoolCallback(StockMatchThreadProc, &tiStock1, &callbackEnviron);
					bool ret4 = TrySubmitThreadpoolCallback(ScopeMatchThreadProc, &tiScope1, &callbackEnviron);
				}
				else if (i == 1) {
					tiMuzzle2.image = src;
					tiMuzzle2.index = 1;
					tiMuzzle2._this = this;
					tiGrip2.image = src;
					tiGrip2.index = 1;
					tiGrip2._this = this;
					tiStock2.image = src;
					tiStock2.index = 1;
					tiStock2._this = this;
					tiScope2.image = src;
					tiScope2.index = 1;
					tiScope2._this = this;
					bool ret1 = TrySubmitThreadpoolCallback(MuzzleMatchThreadProc, &tiMuzzle2, &callbackEnviron);
					bool ret2 = TrySubmitThreadpoolCallback(GripMatchThreadProc, &tiGrip2, &callbackEnviron);
					bool ret3 = TrySubmitThreadpoolCallback(StockMatchThreadProc, &tiStock2, &callbackEnviron);
					bool ret4 = TrySubmitThreadpoolCallback(ScopeMatchThreadProc, &tiScope2, &callbackEnviron);
				}
				

				/*bool muzzleMatched = false;
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
				}*/

				/*bool gripMatched = false;
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
				}*/

				/*bool stockMatched = false;
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
				}*/

				/*bool scopeMatched = false;
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
				}*/


			}
			/*weaponList[i]->ComputeYOffset();*/
			SendMessageA(hWnd, WM_CUSTOM_MESSAGE_PICK_WEAPON, currentIndexPosition, 0);
			break;			
		}
	}
}

void GameStart::MatchTabOpen(Mat* src)
{
	packageOpened = matchWeapon.MatchTabOpenImage(src, &tabOpenMatchImage, &tabOpenMatchImageMask,tabOpenRect);
	if (packageOpened) {
		PickMatchImageWeapon();
	}	
}

void GameStart::MatchStance(Mat* src)
{
	int stance = matchWeapon.MatchStanceImage(src, &stanceMatchCrouchImage, &stanceMatchCrouchImageMask, &stanceMatchProneImage, &stanceMatchProneImageMask, stanceRect);
	if (stance == 0) {
		isCrouch = false;
		isProne = false;
		CurrentWeapon->Crouch(false);
		CurrentWeapon->Prone(false);
	}
	else if (stance == 1) {
		isCrouch = true;
		isProne = false;
		CurrentWeapon->Crouch(true);
	}
	else if (stance == 2) {
		isProne = true;
		isCrouch = false;
		CurrentWeapon->Prone(true);
	}

	SetMessage();
}

void GameStart::IsAds()
{
	//先默认是ADS模式，然后再根据图像识别判断正确情况
	adsOpened = true;
	DoMatchAdsOpen();

	
}

void GameStart::MatchAds(Mat* src)
{
	adsOpened = matchWeapon.MatchAdsOpenImage(src, &adsMatchImage, &adsMatchImageMask, adsRect);
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
	LoadSwitchCrouch();
	LoadSwitchProne();
	LoadSwitchADS();
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

	//matchWeapon.SaveMask("");

	/*for (auto t : WEAPON_LIB.weaponList) {
		if(t->weaponName != "Default")
		matchWeapon.SaveMask(t->weaponName);
	}*/

	/*for (auto t : WEAPON_LIB.muzzleList) {
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
	}*/
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
	switch (key) {
	case 0x31: //1
	{	
		if (keyDownOrUp == 1) {
			keyboardState.isNum1Press = 1;
			//取消ads
			CancelAds();
		}
		else {
			keyboardState.isNum1Press = 0;
			keyboardState.canFocus = FALSE;
			SwitchWeapon(1);

			SetMessage();
		}
	}
	break;
	case 0x32:	//2
	{	
		if (keyDownOrUp == 1) {
			keyboardState.isNum2Press = 1;
			//取消ads
			CancelAds();
		}
		else {
			keyboardState.isNum2Press = 0;
			keyboardState.canFocus = TRUE;
			SwitchWeapon(2);

			SetMessage();
		}
	}
	break;
	case 0x33:	//3
	{
		if (keyDownOrUp == 1) {
			keyboardState.isNum3Press = 1;
			//取消ads
			CancelAds();
		}
		else {
			keyboardState.isNum3Press = 0;
		}
	}
	break;
	case 0x34:	//4
	{
		if (keyDownOrUp == 1) {
			keyboardState.isNum4Press = 1;
			//取消ads
			CancelAds();
		}
		else {
			keyboardState.isNum4Press = 0;
		}
	}
	break;
	case 0x35:	//5
	{
		if (keyDownOrUp == 1) {
			keyboardState.isNum5Press = 1;
			//取消ads
			CancelAds();
		}
		else {
			keyboardState.isNum5Press = 0;
		}
	}
	break;
	case 0x36:	//6
	{
		if (keyDownOrUp == 1) {
			keyboardState.isNum6Press = 1;
			//取消ads
			CancelAds();
		}
		else {
			keyboardState.isNum6Press = 0;
		}
	}
	break;
	case 0x43:	//C
	{
		if (keyDownOrUp == 1) {
			keyboardState.isC_Press = 1;
		}
		else {
			keyboardState.isC_Press = 0;
		}
	}
	break;
	case 0x5A:	//Z
	{
		if (keyDownOrUp == 1) {
			keyboardState.isZ_Press = 1;
		}
		else {
			keyboardState.isZ_Press = 0;
		}
	}
	break;
	case 0x52:	//R
	{
		if (keyDownOrUp == 1) {
			Reload();
			//取消ads
			CancelAds();
		}
		else {

		}
	}
	break;
	case 0x58:	//X
	{
		if (keyDownOrUp == 1) {
			keyboardState.canFocus = FALSE;
			//取消ads
			CancelAds();
		}
		else {

		}
	}
	break;
	case 0x47:	//G
	{
		if (keyDownOrUp == 1) {
			//取消ads
			CancelAds();
		}
		else {

		}
	}
	break;
	case 0xC0:	//~`
	{
		if (keyDownOrUp == 1) {

		}
		else {

		}
	}
	break;
	case VK_NUMPAD1:
	{
		if (keyDownOrUp == 1) {

		}
		else {
			MoveTest(5);
			SetMessage();
		}
	}
	break;
	case VK_NUMPAD2:
	{
		if (keyDownOrUp == 1) {
			MoveTest(100);
			SetMessage();
		}
		else {

		}
	}
	break;
	case VK_NUMPAD3:
	{
		if (keyDownOrUp == 1) {

		}
		else {
			countPx = 0;
			SetMessage();
		}
	}
	break;
	case VK_NUMPAD4:
	{
		if (keyDownOrUp == 1) {

		}
		else {
			MoveTest(-5);
			SetMessage();
		}
	}
	break;
	case VK_NUMPAD5:
	{
		if (keyDownOrUp == 1) {
			MoveTest(-100);
			SetMessage();
		}
		else {

		}
	}
	break;
	case VK_NUMPAD6:
	{
		if (keyDownOrUp == 1) {

		}
		else {

		}
	}
	break;
	case VK_NUMPAD7:
	{
		if (keyDownOrUp == 1) {

		}
		else {

		}
	}
	break;
	case VK_NUMPAD8:
	{
		if (keyDownOrUp == 1) {

		}
		else {

		}
	}
	break;
	case VK_NUMPAD9:
	{
		if (keyDownOrUp == 1) {

		}
		else {

		}
	}
	break;
	case VK_NUMPAD0:
	{
		if (keyDownOrUp == 1) {

		}
		else {
			CurrentWeapon->ResetWeapon();
			PickWeapon("Default");
		}
	}
	break;
	case VK_DIVIDE:
	{
		if (keyDownOrUp == 1) {

		}
		else {

		}
	}
	break;
	case VK_MULTIPLY:
	{
		if (keyDownOrUp == 1) {

		}
		else {

		}
	}
	break;
	case VK_SUBTRACT:
	{
		if (keyDownOrUp == 1) {

		}
		else {

		}
	}
	break;
	case VK_ADD:
	{
		if (keyDownOrUp == 1) {

		}
		else {

		}
	}
	break;
	case VK_UP:
	{
		if (keyDownOrUp == 1) {

		}
		else {

		}
	}
	break;
	case VK_DOWN:
	{
		if (keyDownOrUp == 1) {

		}
		else {

		}
	}
	break;
	case VK_LEFT:
	{
		if (keyDownOrUp == 1) {

		}
		else {

		}
	}
	break;
	case VK_RIGHT:
	{
		if (keyDownOrUp == 1) {

		}
		else {

		}
	}
	break;
	case VK_TAB:
	{
		if (keyDownOrUp == 1) {
			if (keyboardState.isTabPress == 0) {
				keyboardState.isTabPress = 1;
				if (packageOpened) {
					packageOpened = false;
				}
				else {
					CreateTimerQueueTimer(&m_timerHandle3, NULL, TimerProc3, this, 150, 0, WT_EXECUTEINTIMERTHREAD);
				}
				
			}

			//取消ads
			CancelAds();
		}
		else {
			if (keyboardState.isTabPress == 1) {
				keyboardState.isTabPress = 0;
			}
		}
	}
	break;
	case VK_LCONTROL:
	{
		if (keyDownOrUp == 1) {
			keyboardState.isLeftContrlPress = 1;
		}
		else {
			keyboardState.isLeftContrlPress = 0;
		}
	}
	break;
	case VK_LSHIFT:
	{
		if (keyDownOrUp == 1) {
			keyboardState.isLeftShiftPress = 1;
		}
		else {
			keyboardState.isLeftShiftPress = 0;
		}
	}
	break;
	case VK_RSHIFT:
	{
		if (keyDownOrUp == 1) {
			keyboardState.isRightShiftPress = 1;
		}
		else {
			keyboardState.isRightShiftPress = 0;
		}
	}
	break;
	case VK_CAPITAL:
	{
		if (keyDownOrUp == 1) {
			keyboardState.isCapsLockPress = 1;
		}
		else {
			short key = GetKeyState(VK_CAPITAL);
			keyboardState.capsLock = key & 0x0001;
			keyboardState.isCapsLockPress = 0;
		}
	}
	break;
	case VK_SCROLL:
	{
		if (keyDownOrUp == 1) {

		}
		else {
			short key = GetKeyState(VK_SCROLL);
			keyboardState.scrollLock = key & 0x0001;
		}
	}
	break;
	case VK_LMENU:
	{
		if (keyDownOrUp == 1) {
			keyboardState.isLeftAltPress = 1;
		}
		else {
			keyboardState.isLeftAltPress = 0;
		}
	}
	break;
	}


	//处理绑定按键
	if (key == crouchKey) {
		if (keyDownOrUp == 1) {
			if (SWITCH_CROUCH == 1) {

			}
			else {
				if (!isProne && !isCrouch) {
					CurrentWeapon->Crouch(true);
				}
				isCrouch = true;
			}
		}
		else {
			if (SWITCH_CROUCH == 1) {
				if (isCrouch) {
					isCrouch = false;
					CurrentWeapon->Crouch(false);
				}
				else {
					DoMatchStance();
				}
			}
			else {
				if (!isProne && isCrouch) {
					CurrentWeapon->Crouch(false);
				}
				isCrouch = false;
			}

		}
	}
	else if (key == proneKey) {
		if (keyDownOrUp == 1) {
			if (SWITCH_PRONE == 1) {

			}
			else {
				if (!isCrouch && !isProne) {
					CurrentWeapon->Prone(true);
				}
				isProne = true;
			}

		}
		else {
			if (SWITCH_PRONE == 1) {
				if (isProne) {
					isProne = false;
					CurrentWeapon->Prone(false);
				}
				else {
					DoMatchStance();
				}
			}
			else {
				if (!isCrouch && isProne) {
					CurrentWeapon->Prone(false);
				}
				isProne = false;
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

	//ALT 1 - 6 
	if (keyboardState.isLeftAltPress && keyboardState.isNum1Press) {
		AssembleScope(1);
		SetMessage();
	}
	if (keyboardState.isLeftAltPress && keyboardState.isNum2Press) {
		AssembleScope(2);
		SetMessage();
	}
	if (keyboardState.isLeftAltPress && keyboardState.isNum3Press) {
		AssembleScope(3);
		SetMessage();
	}
	if (keyboardState.isLeftAltPress && keyboardState.isNum4Press) {
		AssembleScope(4);
		SetMessage();
	}
	if (keyboardState.isLeftAltPress && keyboardState.isNum5Press) {
		AssembleScope(6);
		SetMessage();
	}
	if (keyboardState.isLeftAltPress && keyboardState.isNum6Press) {
		AssembleScope(8);
		SetMessage();
	}
	if (keyboardState.isLeftAltPress && keyboardState.isT_Press) {

	}

	SetMessage();
}



void GameStart::DoMouseEvent(unsigned short key, unsigned int data)
{
	switch (key)
	{
	case WM_LBUTTONDOWN: 
	{
		mouseState.isLeftButtonPress = 1;
	}		
	break;
	case WM_LBUTTONUP:
	{
		mouseState.isLeftButtonPress = 0;
	}	
	break;
	case WM_LBUTTONDBLCLK: {

	}
	break;
	case WM_RBUTTONDOWN:
	{
		mouseState.isRightButtonPress = 1;
		if (SWITCH_PRONE == 1 || SWITCH_CROUCH == 1) {
			CreateTimerQueueTimer(&m_timerHandle2, NULL, TimerProc2, this, 50, 0, WT_EXECUTEINTIMERTHREAD);
		}

		if (keyboardState.canFocus) {
			CreateTimerQueueTimer(&m_timerHandle5, NULL, TimerProc5, this, 300, 0, WT_EXECUTEINTIMERTHREAD);
		}
	}	
	break;
	case WM_RBUTTONUP:
	{
		mouseState.isRightButtonPress = 0;
		if (SWITCH_ADS == 1) {
			CreateTimerQueueTimer(&m_timerHandle, NULL, TimerProc, this, 50, 0, WT_EXECUTEINTIMERTHREAD);
			//IsAds();
		}

		if (keyboardState.canFocus) {
			DeleteTimerQueueTimer(NULL, m_timerHandle5, NULL);
			KeyboardInput(VK_RSHIFT, FALSE);
		}
	}
	break;
	case WM_RBUTTONDBLCLK: {

	}
	break;
	case WM_MOUSEWHEEL: {
		if (keyboardState.isLeftAltPress) {
			short delta = (short)data;
			if (delta > 0) {    //滚轮上
				PickPreviousWeapon();
				SetMessage();
			}
			else if (delta < 0) {   //滚轮下
				PickNextWeapon();
				SetMessage();
			}
		}

		if (keyboardState.isLeftContrlPress) {
			short delta = (short)data;
			if (delta > 0) {    //滚轮上
				DecrementRecoil();
				SetMessage();
			}
			else if (delta < 0) {   //滚轮下
				IncrementRecoil();
				SetMessage();
			}
		}
	}
	break;
	case WM_MBUTTONDOWN: {

	}
	break;
	case WM_MBUTTONUP: {

	}
	break;
	
	}

	//特殊处理
	//辅助镜切换
	if (keyboardState.isLeftContrlPress && key == WM_MBUTTONDOWN && !mouseState.isLeftButtonPress) {
		KeyboardInput(VK_SCROLL, TRUE);
		KeyboardInput(VK_SCROLL, FALSE);

		short key = GetKeyState(VK_SCROLL);
		keyboardState.scrollLock = key & 0x0001;
	}

	//保存配置
	if (keyboardState.isLeftAltPress && key == WM_MBUTTONDOWN) {
		CurrentWeapon->ChangeSetting();
	}

	//屏息
	if (isHoldBreath && mouseState.isRightButtonPress) {
		CurrentWeapon->HoldBreath(true);
		SetMessage();
	}
	else {
		CurrentWeapon->HoldBreath(false);
		SetMessage();
	}


	SetMessage();
}

void GameStart::CancelAds()
{
	adsOpened = false;
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

void GameStart::LoadSwitchCrouch()
{
	SWITCH_CROUCH = GetPrivateProfileIntA("General", "SwitchCrouch", 50, INI_FILE_PATH.c_str());
}

void GameStart::SetSwitchCrouch(int sc)
{
	SWITCH_CROUCH = sc;
	WritePrivateProfileStringA("General", "SwitchCrouch", std::to_string(SWITCH_CROUCH).c_str(), INI_FILE_PATH.c_str());
}

void GameStart::LoadSwitchProne()
{
	SWITCH_PRONE = GetPrivateProfileIntA("General", "SwitchProne", 50, INI_FILE_PATH.c_str());
}

void GameStart::SetSwitcProne(int sp)
{
	SWITCH_PRONE = sp;
	WritePrivateProfileStringA("General", "SwitchProne", std::to_string(SWITCH_PRONE).c_str(), INI_FILE_PATH.c_str());
}



void GameStart::LoadSwitchADS()
{
	SWITCH_ADS = GetPrivateProfileIntA("General", "SwitchADS", 50, INI_FILE_PATH.c_str());
}

void GameStart::SetSwitcADS(int sp)
{
	SWITCH_ADS = sp;
	WritePrivateProfileStringA("General", "SwitchADS", std::to_string(SWITCH_ADS).c_str(), INI_FILE_PATH.c_str());
}

void GameStart::KeyboardInput(UINT key, BOOL isKeyDown) {
	UINT scanCode = MapVirtualKey(key, MAPVK_VK_TO_VSC_EX);
	if (isKeyDown) {
		keybd_event(key, scanCode, 0, 0);
	}
	else {
		keybd_event(key, scanCode, KEYEVENTF_KEYUP, 0);

	}
}


void CALLBACK GameStart::TimerProc(void* gameStart, BOOLEAN TimerOrWaitFired) {
	((GameStart*)gameStart)->IsAds();
}

void CALLBACK GameStart::TimerProc2(void* gameStart, BOOLEAN TimerOrWaitFired) {
	((GameStart*)gameStart)->DoMatchStance();
}

void CALLBACK GameStart::TimerProc3(void* gameStart, BOOLEAN TimerOrWaitFired) {
	GameStart* pGameStart = (GameStart*)gameStart;
	if (pGameStart->allowMatch) {
		pGameStart->allowMatch = false;
		CreateTimerQueueTimer(&pGameStart->m_timerHandle4, NULL, TimerProc4, gameStart, 1000, 0, WT_EXECUTEINTIMERTHREAD);
		pGameStart->CanDoMatchWeapon();
	}

}
void CALLBACK GameStart::TimerProc4(void* gameStart, BOOLEAN TimerOrWaitFired) {
	GameStart* pGameStart = (GameStart*)gameStart;
	pGameStart->allowMatch = true;
}

void CALLBACK GameStart::TimerProc5(void* gameStart, BOOLEAN TimerOrWaitFired) {
	GameStart* pGameStart = (GameStart*)gameStart;
	pGameStart->KeyboardInput(VK_RSHIFT, TRUE);
}


void CALLBACK GameStart::WeaponMatchThreadProc(_Inout_ PTP_CALLBACK_INSTANCE Instance, _Inout_opt_ PVOID Context) {
	ThisAndIndex* ti = (ThisAndIndex*)Context;
	ti->_this->Match(ti->image,ti->index);
}

void CALLBACK GameStart::CanMatchWeaponThreadProc(_Inout_ PTP_CALLBACK_INSTANCE Instance, _Inout_opt_ PVOID Context) {
	ThisAndIndex* ti = (ThisAndIndex*)Context;
	ti->_this->MatchTabOpen(ti->image);
	SetMessage();
}

void CALLBACK GameStart::StanceMatchThreadProc(_Inout_ PTP_CALLBACK_INSTANCE Instance, _Inout_opt_ PVOID Context) {
	ThisAndIndex* ti = (ThisAndIndex*)Context;
	ti->_this->MatchStance(ti->image);
}

void CALLBACK GameStart::AdsMatchThreadProc(_Inout_ PTP_CALLBACK_INSTANCE Instance, _Inout_opt_ PVOID Context) {
	ThisAndIndex* ti = (ThisAndIndex*)Context;
	ti->_this->MatchAds(ti->image);
}

void CALLBACK GameStart::MuzzleMatchThreadProc(PTP_CALLBACK_INSTANCE Instance, PVOID Context)
{
	ThisAndIndex* ti = (ThisAndIndex*)Context;
	bool muzzleMatched = false;
	for (auto m : WEAPON_LIB.muzzleList) {
		if (!muzzleMatched) {
			int matched = ti->_this->matchWeapon.MatchAttachmentImage(ti->image, &m->templateImage, &m->maskImage, ti->_this->muzzleRect, ti->_this->gripRect, ti->_this->stockRect, ti->_this->scopeRect);
			if (matched == 1) {
				ti->_this->weaponList[ti->index]->AssembleMuzzle(m);
				muzzleMatched = true;
			}
		}
	}
	if (!muzzleMatched) {
		ti->_this->weaponList[ti->index]->AssembleMuzzle(WEAPON_LIB.FindMuzzle("Muzzle_None"));
	}

	ti->_this->weaponList[ti->index]->ComputeYOffset();
	SetMessage();
}

void CALLBACK GameStart::GripMatchThreadProc(PTP_CALLBACK_INSTANCE Instance, PVOID Context)
{
	ThisAndIndex* ti = (ThisAndIndex*)Context;
	bool gripMatched = false;
	for (auto m : WEAPON_LIB.gripList) {
		if (!gripMatched) {
			int matched = ti->_this->matchWeapon.MatchAttachmentImage(ti->image, &m->templateImage, &m->maskImage, ti->_this->muzzleRect, ti->_this->gripRect, ti->_this->stockRect, ti->_this->scopeRect);
			if (matched == 2) {
				ti->_this->weaponList[ti->index]->AssembleGrip(m);
				gripMatched = true;
			}
		}
	}
	if (!gripMatched) {
		ti->_this->weaponList[ti->index]->AssembleGrip(WEAPON_LIB.FindGrip("Grip_None"));
	}

	ti->_this->weaponList[ti->index]->ComputeYOffset();
	SetMessage();
}

void CALLBACK GameStart::StockMatchThreadProc(PTP_CALLBACK_INSTANCE Instance, PVOID Context)
{
	ThisAndIndex* ti = (ThisAndIndex*)Context;
	bool stockMatched = false;
	for (auto m : WEAPON_LIB.stockList) {
		if (!stockMatched) {
			int matched = ti->_this->matchWeapon.MatchAttachmentImage(ti->image, &m->templateImage, &m->maskImage, ti->_this->muzzleRect, ti->_this->gripRect, ti->_this->stockRect, ti->_this->scopeRect);
			if (matched == 3) {
				ti->_this->weaponList[ti->index]->AssembleStock(m);
				stockMatched = true;
			}
		}
	}
	if (!stockMatched) {
		ti->_this->weaponList[ti->index]->AssembleStock(WEAPON_LIB.FindStock("Stock_None"));
	}

	ti->_this->weaponList[ti->index]->ComputeYOffset();
	SetMessage();
}

void CALLBACK GameStart::ScopeMatchThreadProc(PTP_CALLBACK_INSTANCE Instance, PVOID Context)
{
	ThisAndIndex* ti = (ThisAndIndex*)Context;
	bool scopeMatched = false;
	for (auto m : WEAPON_LIB.scopeList) {
		if (!scopeMatched) {
			int matched = ti->_this->matchWeapon.MatchAttachmentImage(ti->image, &m->templateImage, &m->maskImage, ti->_this->muzzleRect, ti->_this->gripRect, ti->_this->stockRect, ti->_this->scopeRect);
			if (matched == 4) {
				ti->_this->weaponList[ti->index]->AssembleScope(m);
				scopeMatched = true;
			}
		}
	}
	if (!scopeMatched) {
		CScope* scope = WEAPON_LIB.FindCScope(0);
		ti->_this->weaponList[ti->index]->AssembleScope(scope);
	}

	ti->_this->weaponList[ti->index]->ComputeYOffset();
	SetMessage();
}





