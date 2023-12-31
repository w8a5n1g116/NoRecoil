#pragma once
#include "framework.h"
#include "CMuzzle.hpp"
#include "CStock.hpp"
#include "CGrip.hpp"
#include "CMagazine.hpp"
#include "CScope.hpp"

class CWeapon
{
public:
	static enum WEAPON_FUNCTION{FUNCTION1,FUNCTION2};
	/*int data[35] = {
		0,0,0,0,0,
		0,0,0,0,0,
		87,80,72,68,64,
		61,57,54,50,48,
		46,44,42,41,39,
		37,36,35,33,32,
		31,30,29,28,27
	};*/
	string weaponName = "";
	string weaponName2 = "";
	int interval = 1;
	int intervalStand = 0;
	int intervalCrouch = 0;
	int intervalProne = 0;
	vector<int> offset = {};
	CMuzzle* muzzle = nullptr;
	CGrip* grip = nullptr;
	CMagazine* magazine = nullptr;
	CStock* stock = nullptr;
	CScope* cscope = nullptr;
	int scope =1;
	int scopeTemp = 1;
	bool isHoldBreath = false;
	int currentShot = 0;
	int shotCount = 0;

	float scope1X_Scale = 1.0;
	float scope1_5X_Scale = 1.43;
	float scope2X_Scale = 2.0;
	float scope3X_Scale = 3.0;
	float scope4X_Scale = 4.0;
	float scope6X_Scale = 6.0;
	float scope8X_Scale = 8.0;
	float moveY = 0;
	float moveYStand = 0;
	float moveYCrouch = 0;
	float moveYProne = 0;
	int recoil = 0;
	int recoilStand = 0;
	int recoilCrouch = 0;
	int recoilProne = 0;
	float currentRecoil = 0;
	float currentRecoil_2 = 0;
	int aimRecoil = 4;
	float crouchEffect = 0.8;
	float proneEffect = 0.6;

	int moveDistance = 0;
	Mat templateImage;
	Mat maskImage;
	WEAPON_FUNCTION function = FUNCTION2;

	std::string iniFilePath =  ".\\config.ini";

	CWeapon();

	CWeapon(string weaponName, int interval, vector<int> offset, int shotCount);

	CWeapon(string weaponName,string weaponName2, WEAPON_FUNCTION function) :weaponName(weaponName),weaponName2(weaponName2), function(function) {

		int screenWidth = GetSystemMetrics(SM_CXFULLSCREEN);
		string imageSuffix = "";
		if (screenWidth == 2560) {
			imageSuffix = "_1440";
		}
		else if (screenWidth == 2048) {
			imageSuffix = "";
		}
		else if (screenWidth == 1920) {
			imageSuffix = "_1080";
		}

		templateImage = imread("image/template/" + weaponName + imageSuffix + ".png", IMREAD_COLOR);
		maskImage = imread("image/mask/" + weaponName + imageSuffix + ".png", IMREAD_GRAYSCALE);
	};

	void ComputeYOffset();

	void AssembleMuzzle(CMuzzle* muzzle);

	void AssembleGrip(CGrip* grip);

	void AssembleMagazine(CMagazine* magazine);

	void AssembleStock(CStock* stock);

	void AssembleScope(int scope, CScope* cscope);

	void LoadSetting();
	void ChangeSetting();
	void Crouch(int isCrouch);
	void Prone(int isProne);
	std::vector<int> findMatch(int v);
	void SetParameter(int r);
	void ResetWeapon();
	void HoldBreath(bool b);

	int CalculateRecoil(int sens);

	void LoadWeaponImage();

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




