#include "CWeapon.h"

CWeapon::CWeapon(string weaponName, int interval, vector<int> offset, CMuzzle* muzzle, CGrip* grip, CMagazine* magazine, CStock* stock, int scope)
{
	this->weaponName = weaponName;
	this->interval = interval;
	this->offset = offset;
	this->muzzle = muzzle;
	this->grip = grip;
	this->magazine = magazine;
	this->stock = stock;
	this->scope = scope;
}

int CWeapon::ComputeXOffset(int orginOffset)
{
	int countEeffect = 0;
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
