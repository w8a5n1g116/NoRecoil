#include "CWeapon.h"
#include "GameStart.h"

CWeapon::CWeapon()
{
}

CWeapon::CWeapon(string weaponName, int interval, vector<int> offset, int shotCount)
{
	this->weaponName = weaponName;
	this->interval = interval;
	this->offset = offset;
	this->muzzle = nullptr;
	this->grip = nullptr;
	this->magazine = nullptr;
	this->stock = nullptr;
	this->currentShot = 0;
	this->shotCount = shotCount;
	this->scope = 0;
}

void CWeapon::ComputeYOffset()
{
	float countEeffect = 0;
	if (muzzle != nullptr) {
		countEeffect += muzzle->y_effect;
	}
	if (grip != nullptr) {
		countEeffect += grip->y_effect;
	}
	if (stock != nullptr) {
		countEeffect += stock->y_effect;
	}

	LoadSetting();

	float r = (1 - countEeffect) * recoilStand;
	SetParameter(r);
}

void CWeapon::AssembleMuzzle(CMuzzle* muzzle)
{
	this->muzzle = muzzle;
}

void CWeapon::AssembleGrip(CGrip* grip)
{
	this->grip = grip;
}

void CWeapon::AssembleMagazine(CMagazine* magazine)
{
	this->magazine = magazine;
	if (this->magazine != nullptr) {
		this->shotCount = this->magazine->shots;
	}
}

void CWeapon::AssembleStock(CStock* stock)
{
	this->stock = stock;
}

void CWeapon::AssembleScope(int scope,CScope* cscope)
{
	this->scope = scope;
	this->cscope = cscope;
}

void CWeapon::LoadSetting()
{
	recoil = GetPrivateProfileIntA(weaponName.c_str(), "recoil", 400, iniFilePath.c_str());
	SetParameter(recoil);
	
}

void CWeapon::ChangeSetting()
{
	WritePrivateProfileStringA(weaponName.c_str(), "recoil", std::to_string(recoilStand).c_str(), iniFilePath.c_str());
}


void CWeapon::Crouch(int isCrouch)
{
	if (isCrouch) {
		recoil = recoilCrouch;
		interval = intervalCrouch;
		moveY = moveYCrouch;
	}
	else {
		recoil = recoilStand;
		interval = intervalStand;
		moveY = moveYStand;
	}
	
}

void CWeapon::Prone(int isProne)
{
	if (isProne) {
		recoil = recoilProne;
		interval = intervalProne;
		moveY = moveYProne;
	}
	else {
		recoil = recoilStand;
		interval = intervalStand;
		moveY = moveYStand;
	}
	
}

std::vector<int> CWeapon::findMatch(int v)
{	
	std::vector<int> candidateInterval;
	std::vector<int> candidateY;
	std::vector<int> candidateResult;
	int maxMultiple = 50;
	for (int i = 1; i <= maxMultiple; i++) {
		for (int j = 0; j < 35; j++) {
			int r = 0;
			if (GameStart::DataMatrix.size() == 35) {
				r= v - (GameStart::DataMatrix[j] * i);
			}						
			if (r <= 5 && r >= -5) {
				candidateInterval.push_back(j);
				candidateY.push_back(i);
				candidateResult.push_back(r);
			}
		}
	}

	if (candidateResult.size() > 0) {
		int temp = candidateResult[0];
		int position = 0;
		for (int i = 0; i < candidateResult.size(); i++) {
			if (candidateResult[i] < 0) {
				candidateResult[i] *= -1;
			}
		}
		for (int i = 1; i < candidateResult.size(); i++) {
			if (temp > candidateResult[i]) {
				temp = candidateResult[i];
				position = i;
			}
		}

		std::vector<int> findResult;
		findResult.push_back(candidateInterval[position]);
		findResult.push_back(candidateY[position]);

		int _interval = candidateInterval[position];
		int _moveY = candidateY[position];

		return std::vector<int>{_interval, _moveY};

	}

	return std::vector<int>{};
}

void CWeapon::SetParameter(int r)
{
	recoilStand = r;
	auto vecStand = findMatch(recoilStand);
	if (vecStand.size() != 0) {
		intervalStand = vecStand[0];
		moveYStand = vecStand[1];
	}

	recoilCrouch = recoilStand * crouchEffect;
	auto vecCrouch = findMatch(recoilCrouch);
	if (vecCrouch.size() != 0) {
		intervalCrouch = vecCrouch[0];
		moveYCrouch = vecCrouch[1];
	}

	recoilProne = recoilStand * proneEffect;
	auto vecProne = findMatch(recoilProne);
	if (vecProne.size() != 0) {
		intervalProne = vecProne[0];
		moveYProne = vecProne[1];
	}
	
	recoil = recoilStand;
	interval = intervalStand;
	moveY = moveYStand;
}

void CWeapon::ResetWeapon()
{
	scope = 0;
	muzzle = nullptr;
	grip = nullptr;
	stock = nullptr;
}

void CWeapon::HoldBreath(bool b)
{
	if (b) {
		if (!isHoldBreath) {
			isHoldBreath = true;
			scopeTemp = scope;
			scope = 5;
		}	
	}
	else {
		if (isHoldBreath) {
			scope = scopeTemp;
			isHoldBreath = false;
		}
		
	}
	
}

int CWeapon::CalculateRecoil(int sens)
{
	float t = exp(-0.05 * sens);
	float r = t * 1936.31;
	return (int)r;
}
