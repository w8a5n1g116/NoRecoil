#pragma once
#include "framework.h"
#include "CMuzzle.h"
#include "CStock.h"
#include "CGrip.h"
#include "CMagazine.h"
#include "CScope.h"

class CWeapon
{
public:
	static enum WEAPON_FUNCTION{FUNCTION1,FUNCTION2};
	
	string weaponName = "";
	
	CMuzzle* muzzle = nullptr;
	CGrip* grip = nullptr;
	CMagazine* magazine = nullptr;
	CStock* stock = nullptr;
	CScope* scope = nullptr;

	bool isHoldBreath = false;
	double recoilBase = 300;
	double recoilBaseRunning = 300;
	vector<double> recoilRates = {
		1,1,1,1,1,
		1,1,1,1,1,
		1,1,1,1,1,
		1,1,1,1,1,
		1,1,1,1,1,
		1,1,1,1,1,
		1,1,1,1,1,
		1,1,1,1,1,
	};
	int shotInterval = 100;
	int currentShot = 0;
	int shotCount = 42;
	double attachmentEffect = 1.1f;

	double scope1_5X_Scale = 1.43;

	int aimRecoil = 4;
	double crouchEffect = 0.8;
	double proneEffect = 0.55;

	Mat templateImage;
	Mat maskImage;
	WEAPON_FUNCTION function = FUNCTION2;

	CWeapon() {};

	CWeapon(string weaponName, WEAPON_FUNCTION function);

	void ComputeYOffset();

	void AssembleMuzzle(CMuzzle* muzzle);
	void AssembleGrip(CGrip* grip);
	void AssembleMagazine(CMagazine* magazine);
	void AssembleStock(CStock* stock);
	void AssembleScope(CScope* scope);

	void Reload();
	void LoadSetting();
	void ChangeSetting();
	void Crouch(int isCrouch);
	void Prone(int isProne);
	void ResetWeapon();
	void HoldBreath(bool b);


	void SetRecoilRates(vector<double> rates);

	void SetRecoilBase(double base);

	void SetShotInterval(int intval);

	double SensitiveEffect();

	void SetRecoil();

	
};




