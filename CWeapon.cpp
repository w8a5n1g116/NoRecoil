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
