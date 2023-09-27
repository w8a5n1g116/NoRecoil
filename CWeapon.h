#pragma once
#include "framework.h"
#include "CMuzzle.h"
#include "CStock.h"
#include "CGrip.h"
#include "CMagazine.h"
class CWeapon
{
public:
	static enum WEAPON_FUNCTION{FUNCTION1,FUNCTION2};
	string weaponName = "";
	int interval = 20;
	vector<int> offset = {};
	CMuzzle* muzzle = nullptr;
	CGrip* grip = nullptr;
	CMagazine* magazine = nullptr;
	CStock* stock = nullptr;
	int scope =0;
	int currentShot = 0;
	int shotCount = 0;

	int scope1X_Scale = 1;
	int scope1_5X_Scale = 1.5;
	int scope2X_Scale = 2;
	int scope3X_Scale = 3;
	int scope4X_Scale = 4;
	int noAttachmentRecoil = 0;
	int fullAttachmentRecoil = 0;
	int currentRecoil = 0;
	int currentRecoil_2 = 0;
	int aimRecoil = 4;
	WEAPON_FUNCTION function = FUNCTION2;

	std::string iniFilePath = GetUserProfilePath() + "\\config.ini";

	CWeapon();

	CWeapon(string weaponName, int interval, vector<int> offset, CMuzzle* muzzle, CGrip* grip, CMagazine* magazine, CStock* stock, int shotCount, int scope);

	CWeapon(string weaponName, int interval, vector<int> offset, int shotCount);

	CWeapon(string weaponName, WEAPON_FUNCTION function, int noAttachmentRecoil, int fullAttachmentRecoil) :weaponName(weaponName), function(function), noAttachmentRecoil(noAttachmentRecoil), fullAttachmentRecoil(fullAttachmentRecoil) {};

	int ComputeXOffset(int orginOffset);

	void AssembleMuzzle(CMuzzle* muzzle);

	void AssembleGrip(CGrip* grip);

	void AssembleMagazine(CMagazine* magazine);

	void AssembleStock(CStock* stock);

	void AssembleScope(int scope);

	void LoadSetting();
	void ChangeSetting();

	std::string GetUserProfilePath() {
		std::string path = "";
		const char* homeProfile = "USERPROFILE";
		char homePath[1024] = { 0 };

		unsigned int pathSize = GetEnvironmentVariableA(homeProfile, homePath, 1024);

		if (pathSize == 0 || pathSize > 1024)
		{
			// 获取失败 或者 路径太长 
			int ret = GetLastError();
		}
		else
		{
			path = std::string(homePath);
		}
		return path;
	}

	
};




