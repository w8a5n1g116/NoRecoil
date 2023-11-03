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
	//屏幕截图
	Mat screenShot;
	//一号枪位 截图
	Mat weapon1Src;
	//二号枪位 截图
	Mat weapon2Src;
	//判断背包打开位置 截图
	Mat tabOpenSrc;
	//判断姿态位置截图
	Mat stanceSrc;
	//判断Ads是否打开的截图
	Mat adsSrc;

	Mat tabOpenMatchImage;
	Mat tabOpenMatchImageMask;

	Mat stanceMatchCrouchImage;
	Mat stanceMatchCrouchImageMask;

	Mat stanceMatchProneImage;
	Mat stanceMatchProneImageMask;

	Mat adsMatchImage;
	Mat adsMatchImageMask;
	//多线程执行传递参数
	struct ThisAndIndex {
		GameStart* _this;
		Mat* image;
		int index;
	};

	ThisAndIndex ti1;
	ThisAndIndex ti2;
	ThisAndIndex tiTabOpen;
	ThisAndIndex tiStance;
	ThisAndIndex tiAds;

	Rect weaponRect1, weaponRect2, weaponNaceRect, muzzleRect, gripRect, stockRect, scopeRect,tabOpenRect,stanceRect,tabOpenBGRect,stanceBGRect,adsRect,adsBGRect;


	TP_CALLBACK_ENVIRON callbackEnviron;
	//鼠标状态
	Mouse_State mouseState;

	//键盘状态
	KeyBoard_State keyboardState;

	//记录移动像素点
	int countPx = 0;

	HANDLE m_timerHandle = NULL;
	
	CWeapon* weaponList[2] = { 0 };
	CWeapon* CurrentWeapon = nullptr;
	int currentPosition = 1;
	//用于控制单发枪是否可以下一发
	bool enableTrigger = true;
	//记录枪在小窗口显示的位置
	int currentIndexPosition = 0;
	int currentIndexPosition1 = 0;
	int currentIndexPosition2 = 0;
	//默认键位
	unsigned short crouchKey = VK_LSHIFT;
	bool isCrouch = false;
	unsigned short proneKey = VK_CAPITAL;
	bool isProne = false;
	unsigned short focusKey = VK_LCONTROL;
	bool isFocus = false;
	unsigned short holdBreathKey = VK_LMENU;
	bool isHoldBreath = false;
	//控制是否需要识别枪    
	bool allowMatch = true;
	//分辨率
	static int RESOLUTION_TYPE;	//0->1440p,1->1440p*125%,2->1080p
	//开镜灵敏度
	static int SENSITIVE;
	//是否右键切换开镜
	static int SWITCH_ADS;
	//是否切换蹲
	static int SWITCH_CROUCH;
	//是否切换趴
	static int SWITCH_PRONE;
	//背包是否打开                                                                        
	bool packageOpened = false;

	//是否已右键开镜
	bool adsOpened = false;
	
	Rect p1440WeaponRect1 = Rect(1769, 117, 657, 255);
	Rect p1440WeaponRect2 = Rect(1769, 391, 657, 255);
	Rect p1440WeaponNameXY = Rect(51, 59, 0, 7);
	Rect p1440MuzzleXY = Rect(2, 10, 185, 193);
	Rect p1440GripXY = Rect(138, 146, 185, 193);
	Rect p1440StockXY = Rect(568, 576, 185, 193);
	Rect p1440ScopeXY = Rect(365, 373, 34, 42);
	Rect p1440TabOpenRect = Rect(460, 55, 160, 65);	//460,55,620,120
	Rect p1440StanceRect = Rect(900, 1290, 100, 110);	//900,1290,1000,1400
	Rect p1440adsRect = Rect(1200, 1150, 170, 80);
	Rect p1440TabOpenXY = Rect(34, 40, 20, 26);	//37,23,114,59
	Rect p1440StanceXY = Rect(32,38, 25, 31);	//35,28,91,76	
	Rect p1440adsXY = Rect(50, 56, 23, 29);	//53,26,104,39

	Rect p1440_125WeaponRect1 = Rect(1772, 120, 648, 255);
	Rect p1440_125WeaponRect2 = Rect(1772, 394, 648, 255);
	Rect p1440_125WeaponNameXY = Rect(40, 46, 0, 6);
	Rect p1440_125MuzzleXY = Rect(0, 6, 182, 190);
	Rect p1440_125GripXY = Rect(132, 140, 182, 190);
	Rect p1440_125StockXY = Rect(562, 572, 182, 190);
	Rect p1440_125ScopeXY = Rect(362, 372, 28, 42);
	Rect p1440_125TabOpenRect = Rect(0, 0, 0, 0);
	Rect p1440_125StanceRect = Rect(0, 0, 0, 0);
	Rect p1440_125adsRect = Rect(0, 0, 0, 0);
	Rect p1440_125TabOpenXY = Rect(0, 0, 0, 0);
	Rect p1440_125StanceXY = Rect(0, 0, 0, 0);
	Rect p1440_125adsXY = Rect(0, 0, 0, 0);

	Rect p1080WeaponRect1 = Rect(1322, 82, 485, 198);
	Rect p1080WeaponRect2 = Rect(1322, 287, 485, 198);
	Rect p1080WeaponNameXY = Rect(40, 48, 2, 10);
	Rect p1080MuzzleXY = Rect(7, 15, 144, 152);
	Rect p1080GripXY = Rect(109, 117, 144, 152);
	Rect p1080StockXY = Rect(430, 438, 144, 152);
	Rect p1080ScopeXY = Rect(278, 286, 31, 39);
	Rect p1080TabOpenRect = Rect(340, 40, 150, 50);	//340,40,490,90
	Rect p1080StanceRect = Rect(670, 970, 90, 70);	//670,970, 760,1040
	Rect p1080adsRect = Rect(900, 860, 120, 70);
	Rect p1080TabOpenXY = Rect(29, 35, 14, 20);	//32,17,90,46
	Rect p1080StanceXY = Rect(21, 27, 5, 13);	//24,8,82,55	
	Rect p1080adsXY = Rect(37, 43, 17, 23);	//40, 20, 49, 11
	

	MatchWeapon matchWeapon;

	GameStart();

	void InitWeapon();
	void Move();
	void MoveTest(int y);
	void PickWeapon(std::string weaponName);
	void PickMatchImageWeapon();
	void CanDoMatchWeapon();
	void DoMatchStance();
	void DoMatchAdsOpen();
	void IsAds();
	void Match(Mat* src, int index);
	void MatchTabOpen(Mat* src);
	void MatchStance(Mat* src);
	void MatchAds(Mat* src);
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

	void DoMouseEvent(unsigned short key);

	void LoadKeys();
	void SetCrouchKey(unsigned short key);
	void SetProneKey(unsigned short key);
	void SetFocusKey(unsigned short key);
	void SetHoldBreathKey(unsigned short key);
	void LoadResolution();
	void SelectResolution(int resolution);
	void LoadSensitive();
	void SetSensitive(int sens);
	void LoadSwitchCrouch();
	void SetSwitchCrouch(int sc);
	void LoadSwitchProne();
	void SetSwitcProne(int sp);
	void LoadSwitchADS();
	void SetSwitcADS(int sa);



	static void CALLBACK TimerProc(void* key, BOOLEAN TimerOrWaitFired);

	static void CALLBACK TimerProc2(void* key, BOOLEAN TimerOrWaitFired);

	static void CALLBACK WeaponMatchThreadProc(_Inout_ PTP_CALLBACK_INSTANCE Instance,_Inout_opt_ PVOID Context);

	static void CALLBACK CanMatchWeaponThreadProc(_Inout_ PTP_CALLBACK_INSTANCE Instance, _Inout_opt_ PVOID Context);

	static void CALLBACK StanceMatchThreadProc(_Inout_ PTP_CALLBACK_INSTANCE Instance, _Inout_opt_ PVOID Context);

	static void CALLBACK AdsMatchThreadProc(_Inout_ PTP_CALLBACK_INSTANCE Instance, _Inout_opt_ PVOID Context);
	
};

