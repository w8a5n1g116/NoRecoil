#include "CWeapon.h"

CWeapon::CWeapon()
{
}

CWeapon::CWeapon(string weaponName, int interval, vector<int> offset, CMuzzle* muzzle, CGrip* grip, CMagazine* magazine, CStock* stock, int shotCount, int scope)
{
	this->weaponName = weaponName;
	this->interval = interval;
	this->offset = offset;
	this->muzzle = muzzle;
	this->grip = grip;
	this->magazine = magazine;
	this->stock = stock;
	this->shotCount = shotCount;
	this->scope = scope;
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

int CWeapon::ComputeXOffset(int orginOffset)
{
	float countEeffect = 0;
	if (muzzle != nullptr) {
		countEeffect += muzzle->x_effect;
	}
	if (grip != nullptr) {
		countEeffect += grip->x_effect;
	}
	if (stock != nullptr) {
		countEeffect += stock->x_effect;
	}
	return (1 - countEeffect) * orginOffset;
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

void CWeapon::AssembleScope(int scope)
{
	this->scope = scope;
}

void CWeapon::LoadSetting()
{
	recoil = GetPrivateProfileIntA(weaponName.c_str(), "recoil", 400, iniFilePath.c_str());
	SetParameter(recoil);
	
}

void CWeapon::ChangeSetting()
{
	WritePrivateProfileStringA(weaponName.c_str(), "recoil", std::to_string(recoil).c_str(), iniFilePath.c_str());
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
			int r = v - (data[j] * i);
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
}

int CWeapon::CalculateRecoil(int sens)
{
	float t = exp(-0.05 * sens);
	float r = t * 1936.31;
	return (int)r;
}
