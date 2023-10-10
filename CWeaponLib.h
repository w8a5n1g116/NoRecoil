#pragma once
#include "framework.h"
#include "CWeapon.h"
#include "CMuzzle.hpp"
#include "CGrip.hpp"
#include "CMagazine.hpp"
#include "CStock.hpp"
#include "CScope.hpp"

class CWeaponLib
{
public: 
	CWeapon None = CWeapon("WNone", "", CWeapon::FUNCTION2);
	CWeapon Default		= CWeapon("Default","", CWeapon::FUNCTION2);
	CWeapon Mk47_Mutant		= CWeapon("Mk47 Mutant", "", CWeapon::FUNCTION2);
	CWeapon AKM				= CWeapon("AKM", "", CWeapon::FUNCTION2);
	CWeapon Groza			= CWeapon("Groza", "", CWeapon::FUNCTION2);
	CWeapon Beryl_M762		= CWeapon("Beryl M762", "", CWeapon::FUNCTION2);
	CWeapon ACE32			= CWeapon("ACE32", "", CWeapon::FUNCTION2);
	CWeapon M16A4			= CWeapon("M16A4", "MIBA4", CWeapon::FUNCTION2);
	CWeapon QBZ				= CWeapon("QBZ", "OBZ", CWeapon::FUNCTION2);
	CWeapon SCAR_L			= CWeapon("SCAR-L", "", CWeapon::FUNCTION2);
	CWeapon AUG				= CWeapon("AUG", "", CWeapon::FUNCTION2);
	CWeapon G36C			= CWeapon("G36C", "G36C", CWeapon::FUNCTION2);
	CWeapon K2				= CWeapon("K2", "K2", CWeapon::FUNCTION2);
	CWeapon M416			= CWeapon("M416", "MAIE", CWeapon::FUNCTION2);
	CWeapon FAMAS			= CWeapon("FAMAS", "", CWeapon::FUNCTION2);
	CWeapon DP_28			= CWeapon("DP-28", "DP-28", CWeapon::FUNCTION2);
	CWeapon M249			= CWeapon("M249", "M245", CWeapon::FUNCTION2);
	CWeapon Mk14			= CWeapon("Mk14", "Mki4", CWeapon::FUNCTION1);
	CWeapon SLR				= CWeapon("SLR", "", CWeapon::FUNCTION1);
	CWeapon SKS				= CWeapon("SKS", "", CWeapon::FUNCTION1);
	CWeapon Mk12			= CWeapon("Mk12", "Mki2", CWeapon::FUNCTION1);
	CWeapon Mini14			= CWeapon("Mini14", "Minil4", CWeapon::FUNCTION1);
	CWeapon QBU				= CWeapon("QBU", "", CWeapon::FUNCTION1);
	CWeapon VSS				= CWeapon("VSS", "VSS", CWeapon::FUNCTION2);
	CWeapon Lynx_AMR		= CWeapon("Lynx AMR", "Lynx AMR", CWeapon::FUNCTION1);
	CWeapon AWM				= CWeapon("AWM", "AWM", CWeapon::FUNCTION1);
	CWeapon Kar98k			= CWeapon("Kar98k", "Kar98k", CWeapon::FUNCTION1);
	CWeapon Mosin_Nagant	= CWeapon("Mosin Nagant", "", CWeapon::FUNCTION1);
	CWeapon M24				= CWeapon("M24", "", CWeapon::FUNCTION1);
	CWeapon Win94			= CWeapon("Win94", "Wind4", CWeapon::FUNCTION1);
	CWeapon UMP45			= CWeapon("UMP45", "", CWeapon::FUNCTION2);
	CWeapon Tommy_Gun		= CWeapon("Tommy Gun", "", CWeapon::FUNCTION2);
	CWeapon PP_19_Bizon		= CWeapon("PP-19 Bizon", "PP-19 Bizon", CWeapon::FUNCTION2);
	CWeapon P90				= CWeapon("P90", "Pao", CWeapon::FUNCTION2);
	CWeapon MP5K			= CWeapon("MP5K", "MP5K", CWeapon::FUNCTION2);
	CWeapon MP9				= CWeapon("MP9", "MPS", CWeapon::FUNCTION2);
	CWeapon Vector			= CWeapon("Vector", "", CWeapon::FUNCTION2);
	CWeapon Micro_UZI		= CWeapon("Micro UZI", "", CWeapon::FUNCTION2);
	CWeapon DBS				= CWeapon("DBS", "", CWeapon::FUNCTION1);
	CWeapon S1897			= CWeapon("S1897", "", CWeapon::FUNCTION1);
	CWeapon S686			= CWeapon("S686", "", CWeapon::FUNCTION1);
	CWeapon S12K			= CWeapon("S12K", "", CWeapon::FUNCTION1);
	CWeapon Sawed_Off		= CWeapon("Sawed Off", "", CWeapon::FUNCTION1);
	CWeapon O1R452			= CWeapon("O1R452", "", CWeapon::FUNCTION1);
	CWeapon R1895			= CWeapon("R1895", "", CWeapon::FUNCTION1);
	CWeapon Deagle			= CWeapon("Deagle", "", CWeapon::FUNCTION2);
	CWeapon P1911			= CWeapon("P1911", "", CWeapon::FUNCTION1);
	CWeapon P92				= CWeapon("P92", "", CWeapon::FUNCTION1);
	CWeapon P18C			= CWeapon("P18C", "", CWeapon::FUNCTION2);
	CWeapon Skorpion		= CWeapon("Skorpion", "", CWeapon::FUNCTION2);
	CWeapon MG3_660_RPM		= CWeapon("MG3", "MG3", CWeapon::FUNCTION2);
	CWeapon Dragunov		= CWeapon("Dragunov", "", CWeapon::FUNCTION1);

	vector<CWeapon*> weaponList;
	vector<std::string> weaponNameList;
	vector<std::string> weaponNameList2;
	vector<CMuzzle*> muzzleList;
	vector<CGrip*> gripList;
	vector<CStock*> stockList;
	vector<CScope*> scopeList;

	CMuzzle Muzzle_None = CMuzzle("Muzzle_None", 0.0f);
	CMuzzle AR_COMP = CMuzzle("AR_COMP", 0.2f);
	CMuzzle AR_LOWFIRE = CMuzzle("AR_LOWFIRE", 0.1f);
	CMuzzle AR_LOWSOUND = CMuzzle("AR_LOWSOUND", 0);
	CMuzzle SMG_COMP = CMuzzle("SMG_COMP", 0.2f);
	CMuzzle SMG_LOWFIRE = CMuzzle("SMG_LOWFIRE", 0.1f);
	CMuzzle SMG_LOWSOUND = CMuzzle("SMG_LOWSOUND", 0);
	CMuzzle SNIPER_COMP = CMuzzle("SNIPER_COMP", 0.2f);
	CMuzzle SNIPER_LOWFIRE = CMuzzle("SNIPER_LOWFIRE", 0.1f);
	CMuzzle SNIPER_LOWSOUND = CMuzzle("SNIPER_LOWSOUND", 0);

	CGrip Grip_None = CGrip("Grip_None", 0.0f);
	CGrip Angled = CGrip("Angled", 0);
	CGrip Half = CGrip("Half", 0.08f);
	CGrip Laser = CGrip("Laser", 0);
	CGrip LightWeight = CGrip("LightWeight", 0);
	CGrip Thumb = CGrip("Thumb", 0.08f);
	CGrip Vertical = CGrip("Vertical", 0.15f);

	CMagazine Magazine_None = CMagazine("Magazine_None", 37);
	CMagazine SMG = CMagazine("SMG", 37);
	CMagazine SMG_QUICK = CMagazine("SMG_QUICK", 35);
	CMagazine AR = CMagazine("AR", 42);
	CMagazine AR_QUICK = CMagazine("AR_QUICK", 40);
	CMagazine SNIPER = CMagazine("SNIPER", 8);
	CMagazine SNIPER_QUICK = CMagazine("SNIPER_QUICK", 7);

	CStock Stock_None = CStock("Stock_None", 0.0f);
	CStock Tactical = CStock("Tactical", 0);
	CStock BulletLoop = CStock("BulletLoop", 0);
	CStock CheekPad = CStock("CheekPad", 0.2f);
	CStock Folding = CStock("Folding", 0.2f);
	CStock Heavy = CStock("Heavy", 0.05f);

	CScope Scope_None = CScope("Scope_None", 0, 1.0f);
	CScope Scope_1 = CScope("Scope_1", 1, 1.0f);
	CScope Scope_2 = CScope("Scope_2",2, 2.0f);
	CScope Scope_3 = CScope("Scope_3",3, 3.0f);
	CScope Scope_4 = CScope("Scope_4",4, 4.0f);
	CScope Scope_6 = CScope("Scope_6",6, 6.0f);
	CScope Scope_8 = CScope("Scope_8",8, 8.0f);

	CWeaponLib() {
		weaponList.push_back(&Default);
		weaponList.push_back(&M416);	
		weaponList.push_back(&AKM);
		weaponList.push_back(&SCAR_L);
		weaponList.push_back(&ACE32);
		weaponList.push_back(&AUG);	
		weaponList.push_back(&Beryl_M762);
		weaponList.push_back(&UMP45);
		weaponList.push_back(&Tommy_Gun);
		weaponList.push_back(&PP_19_Bizon);
		weaponList.push_back(&Vector);
		weaponList.push_back(&Micro_UZI);
		weaponList.push_back(&M16A4);
		weaponList.push_back(&Mk47_Mutant);
		weaponList.push_back(&Mini14);
		weaponList.push_back(&SKS);
		weaponList.push_back(&Mk12);
		weaponList.push_back(&SLR);
		weaponList.push_back(&Dragunov);
		weaponList.push_back(&QBU);
		weaponList.push_back(&DP_28);
		weaponList.push_back(&M249);
		weaponList.push_back(&VSS);
		weaponList.push_back(&MP5K);
		weaponList.push_back(&MP9);
		weaponList.push_back(&K2);
		weaponList.push_back(&G36C);
		weaponList.push_back(&QBZ);
		weaponList.push_back(&Groza);
		weaponList.push_back(&FAMAS);
		weaponList.push_back( &Mk14);
		weaponList.push_back(&P90);
		//weaponList.push_back(&Lynx_AMR);
		//weaponList.push_back(&AWM);
		//weaponList.push_back(&O1R452);
		//weaponList.push_back(MG3_660_RPM);
				
		//weaponList.push_back( R1895);
		//weaponList.push_back( Deagle);
		//weaponList.push_back( P1911);
		//weaponList.push_back( P92);
		//weaponList.push_back( P18C);
		//weaponList.push_back( Skorpion);		
		

		

		
		//weaponList.push_back(&Win94);
		//weaponList.push_back(&M24);
		//weaponList.push_back(&Mosin_Nagant);
		//weaponList.push_back(&Kar98k);	
		
		//weaponList.push_back(DBS);
		//weaponList.push_back(S12K);
		//weaponList.push_back(S686);
		//weaponList.push_back(S1897);
		

		for (auto t : weaponList) {
			weaponNameList.push_back(t->weaponName);
		}

		for (auto t : weaponList) {
			weaponNameList2.push_back(t->weaponName2);
		}

		muzzleList.push_back(&Muzzle_None);
		muzzleList.push_back(&AR_COMP);
		muzzleList.push_back(&AR_LOWFIRE);
		muzzleList.push_back(&SMG_COMP);
		muzzleList.push_back(&SMG_LOWFIRE);
		muzzleList.push_back(&SNIPER_COMP);
		muzzleList.push_back(&SNIPER_LOWFIRE);

		gripList.push_back(&Grip_None);
		gripList.push_back(&Half);
		gripList.push_back(&Thumb);
		gripList.push_back(&Vertical);
		
		stockList.push_back(&Stock_None);
		stockList.push_back(&CheekPad);
		stockList.push_back(&Folding);
		stockList.push_back(&Heavy);

		scopeList.push_back(&Scope_None);
		scopeList.push_back(&Scope_1);
		scopeList.push_back(&Scope_2);
		scopeList.push_back(&Scope_3);
		scopeList.push_back(&Scope_4);
		scopeList.push_back(&Scope_6);
		scopeList.push_back(&Scope_8);
	}

	CWeapon* FindWeapon(std::string weaponName) {
		for (auto t : weaponList) {
			if (t->weaponName == weaponName) {
				return t;
			}
		}

		for (auto t : weaponList) {
			if (t->weaponName2 == weaponName) {
				return t;
			}
		}

		return nullptr;
	}

	CMuzzle* FindMuzzle(string name) {
		for (auto t : muzzleList) {
			if (t->name == name) {
				return t;
			}
		}
		return nullptr;
	}

	CGrip* FindGrip(string name) {
		for (auto t : gripList) {
			if (t->name == name) {
				return t;
			}
		}
		return nullptr;
	}

	CStock* FindStock(string name) {
		for (auto t : stockList) {
			if (t->name == name) {
				return t;
			}
		}
		return nullptr;
	}

	CScope* FindCScope(int scope) {
		for (auto t : scopeList) {
			if (t->scope == scope) {
				return t;
			}
		}
		return nullptr;
	}

	int FindWeaponPosition(std::string weaponName) {
		for (int i = 0; i < weaponNameList.size();i++) {
			if (weaponNameList[i] == weaponName) {
				return i;
			}
		}

		for (int i = 0; i < weaponNameList2.size(); i++) {
			if (weaponNameList2[i] == weaponName) {
				return i;
			}
		}

		return -1;
	}
};

