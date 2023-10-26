#pragma once
#include "framework.h"
#include "MatchWeapon.hpp"
#include "CWeaponLib.h"

class GameStart
{
public:

	static CWeaponLib WEAPON_LIB;

	struct KeyBoard_State {
		int isLeftContrlPress = 0;
		int isLeftShiftPress = 0;
		int isRightShiftPress = 0;
		int isLeftAltPress = 0;
		int isC_Press = 0;
		int isZ_Press = 0;
		int isT_Press = 0;
		int isNum1Press = 0;
		int isNum2Press = 0;
		int isNum3Press = 0;
		int isNum4Press = 0;
		int isNum5Press = 0;
		int isNum6Press = 0;
		int isTabPress = 0;
		int capsLock = 0;
		int isCapsLockPress = 0;
		int scrollLock = 0;
		int canFocus = FALSE;
	};

	struct Mouse_State {
		int isRightButtonPress = 0;
		int isLeftButtonPress = 0;
		int continuousTap = FALSE;
		int isStartContinuousTap = FALSE;
		int count = 0;
	};

	Mat screenShot;

	Mat weapon1Src;
	Mat weapon2Src;

	struct ThisAndIndex {
		GameStart* _this;
		Mat* image;
		int index;
	};

	ThisAndIndex ti1;
	ThisAndIndex ti2;

	Rect weaponRect1, weaponRect2, weaponNaceRect, muzzleRect, gripRect, stockRect, scopeRect;


	TP_CALLBACK_ENVIRON callbackEnviron;
	//Êó±ê×´Ì¬
	Mouse_State mouseState;

	//¼üÅÌ×´Ì¬
	KeyBoard_State keyboardState;

	//¼ÇÂ¼ÒÆ¶¯ÏñËØµã
	int countPx = 0;

	
	static vector<int> DataMatrix;
	
	CWeapon* weaponList[2] = { 0 };
	CWeapon* CurrentWeapon = nullptr;
	int currentPosition = 1;
	bool enableTrigger = true;
	HANDLE m_timerHandle = NULL;
	bool go = true;
	int currentIndexPosition = 0;
	int currentIndexPosition1 = 0;
	int currentIndexPosition2 = 0;

	unsigned short crouchKey = VK_LSHIFT;
	bool isCrouch = false;
	unsigned short proneKey = VK_CAPITAL;
	bool isProne = false;
	unsigned short focusKey = VK_LCONTROL;
	bool isFocus = false;
	unsigned short holdBreathKey = VK_LMENU;
	bool isHoldBreath = false;

	bool allowMatch = true;

	
	bool p1440 = 0;
	Rect p1440WeaponRect1 = Rect(1769, 117, 657, 255);
	Rect p1440WeaponRect2 = Rect(1769, 391, 657, 255);
	Rect p1440WeaponNameXY = Rect(51, 59, 0, 7);
	Rect p1440MuzzleXY = Rect(2, 10, 185, 193);
	Rect p1440GripXY = Rect(138, 146, 185, 193);
	Rect p1440StockXY = Rect(568, 576, 185, 193);
	Rect p1440ScopeXY = Rect(365, 373, 34, 42);

	bool p1440_zoom_1_25 = 0;
	Rect p1440_125WeaponRect1 = Rect(1772, 120, 648, 255);
	Rect p1440_125WeaponRect2 = Rect(1772, 394, 648, 255);
	Rect p1440_125WeaponNameXY = Rect(40, 46, 0, 6);
	Rect p1440_125MuzzleXY = Rect(0, 6, 182, 190);
	Rect p1440_125GripXY = Rect(132, 140, 182, 190);
	Rect p1440_125StockXY = Rect(562, 572, 182, 190);
	Rect p1440_125ScopeXY = Rect(362, 372, 28, 42);

	bool p1080 = 0;
	Rect p1080WeaponRect1 = Rect(1322, 82, 485, 198);
	Rect p1080WeaponRect2 = Rect(1322, 287, 485, 198);
	Rect p1080WeaponNameXY = Rect(40, 48, 2, 10);
	Rect p1080MuzzleXY = Rect(7, 15, 144, 152);
	Rect p1080GripXY = Rect(109, 117, 144, 152);
	Rect p1080StockXY = Rect(430, 438, 144, 152);
	Rect p1080ScopeXY = Rect(278, 286, 31, 39);
	

	MatchWeapon matchWeapon;

	GameStart();

	void Move();
	void MoveTest(int y);
	void PickWeapon(std::string weaponName);
	void PickMatchImageWeapon();
	void Match(Mat* src, int index);
	void PickPreviousWeapon();
	void PickNextWeapon();
	void IncrementRecoil();
	void DecrementRecoil();
	void SwitchWeapon(int position);
	void LoadSetting();
	void SaveSetting();
	void SaveScreenShot();
	void Reload();

	void AssembleMuzzle(string name);

	void AssembleGrip(string name);

	void AssembleMagazine(string name);

	void AssembleStock(string name);

	void AssembleScope(int scope);

	void DoKeyBoardEvent(unsigned short key,int keyDownOrUp);

	void LoadKeys();
	void SetCrouchKey(unsigned short key);
	void SetProneKey(unsigned short key);
	void SetFocusKey(unsigned short key);
	void SetHoldBreathKey(unsigned short key);


	static void CALLBACK TimerProc(void* key, BOOLEAN TimerOrWaitFired);

	static void CALLBACK TimerProc2(void* key, BOOLEAN TimerOrWaitFired);

	static void CALLBACK MatchThreadProc(_Inout_ PTP_CALLBACK_INSTANCE Instance,_Inout_opt_ PVOID Context);
	
};

