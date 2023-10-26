#pragma once
#include "framework.h"
#include "CWeapon.h"

class CWeaponLib
{
public: 
	CWeapon None;
	CWeapon Default;
	CWeapon Mk47_Mutant;
	CWeapon AKM;
	CWeapon Groza;
	CWeapon Beryl_M762;
	CWeapon ACE32;
	CWeapon M16A4;
	CWeapon QBZ;
	CWeapon SCAR_L;
	CWeapon AUG;
	CWeapon G36C;
	CWeapon K2;
	CWeapon M416;
	CWeapon FAMAS;
	CWeapon DP_28;
	CWeapon M249;
	CWeapon Mk14;
	CWeapon SLR;
	CWeapon SKS;
	CWeapon Mk12;
	CWeapon Mini14;
	CWeapon QBU;
	CWeapon VSS;
	CWeapon Lynx_AMR;
	CWeapon AWM;
	CWeapon Kar98k;
	CWeapon Mosin_Nagant;
	CWeapon M24;
	CWeapon Win94;
	CWeapon UMP45;
	CWeapon Tommy_Gun;
	CWeapon PP_19_Bizon;
	CWeapon P90;
	CWeapon MP5K;
	CWeapon MP9;
	CWeapon Vector;
	CWeapon Micro_UZI;
	CWeapon DBS;
	CWeapon S1897;
	CWeapon S686;
	CWeapon S12K;
	CWeapon Sawed_Off;
	CWeapon O1R452;
	CWeapon R1895;
	CWeapon Deagle;
	CWeapon P1911;
	CWeapon P92;
	CWeapon P18C;
	CWeapon Skorpion;
	CWeapon MG3_660_RPM;
	CWeapon Dragunov;

	vector<CWeapon*> weaponList;
	vector<std::string> weaponNameList;
	vector<CMuzzle*> muzzleList;
	vector<CGrip*> gripList;
	vector<CStock*> stockList;
	vector<CScope*> scopeList;

	CMuzzle Muzzle_None;
	CMuzzle AR_COMP;
	CMuzzle AR_LOWFIRE;
	CMuzzle AR_LOWSOUND;
	CMuzzle SMG_COMP;
	CMuzzle SMG_LOWFIRE;
	CMuzzle SMG_LOWSOUND;
	CMuzzle SNIPER_COMP;
	CMuzzle SNIPER_LOWFIRE;
	CMuzzle SNIPER_LOWSOUND;

	CGrip Grip_None;
	CGrip Angled;
	CGrip Half;
	CGrip Laser;
	CGrip LightWeight;
	CGrip Thumb;
	CGrip Vertical;

	CMagazine Magazine_None;
	CMagazine SMG;
	CMagazine SMG_QUICK;
	CMagazine AR;
	CMagazine AR_QUICK;
	CMagazine SNIPER;
	CMagazine SNIPER_QUICK;

	CStock Stock_None;
	CStock Tactical;
	CStock BulletLoop;
	CStock CheekPad;
	CStock Folding;
	CStock Heavy;

	CScope Scope_None;
	CScope Scope_1;
	CScope Scope_2;
	CScope Scope_3;
	CScope Scope_4;
	CScope Scope_6;
	CScope Scope_8;

	CWeaponLib();

	void InitAttachment();
	void InitWeapon();

	CWeapon* FindWeapon(std::string weaponName);

	CMuzzle* FindMuzzle(string name);

	CGrip* FindGrip(string name);

	CStock* FindStock(string name);

	CScope* FindCScope(int scope);

	int FindWeaponPosition(std::string weaponName);
};

