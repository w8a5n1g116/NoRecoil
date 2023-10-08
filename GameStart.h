#pragma once
#include "framework.h"
#include "CWeaponLib.h"
#include "MatchWeapon.hpp"
class GameStart
{
public:
	CWeaponLib lib;
	/*CWeapon* weapon1 = lib.FindWeapon("M416");
	CWeapon* weapon2 = lib.FindWeapon("M416");*/
	
	CWeapon* weaponList[2] = { 0 };
	CWeapon* CurrentWeapon = nullptr;
	int currentPosition = 1;
	bool enableTrigger = true;
	HANDLE m_timerHandle = NULL;
	bool go = true;
	int currentIndexPosition = 0;
	int currentIndexPosition1 = 0;
	int currentIndexPosition2 = 0;
	int maxIndex = lib.weaponNameList.size();

	MatchWeapon matchWeapon;

	GameStart() {
		weaponList[0] = lib.FindWeapon("Default");
		weaponList[1] = lib.FindWeapon("Default");
		CurrentWeapon = weaponList[0];
		currentPosition = 1;
	}

	void Move();
	void PickWeapon(std::string weaponName);
	void PickMatchWeapon();
	void PickMatchImageWeapon();
	void PickPreviousWeapon();
	void PickNextWeapon();
	void IncrementRecoil();
	void DecrementRecoil();
	void SwitchWeapon(int position);
	void LoadSetting();
	void SaveSetting();
	void SaveScreenShot();

	void AssembleMuzzle(string name);

	void AssembleGrip(string name);

	void AssembleMagazine(string name);

	void AssembleStock(string name);

	void AssembleScope(int scope);

	static void CALLBACK TimerProc(void* key, BOOLEAN TimerOrWaitFired);
	
};

