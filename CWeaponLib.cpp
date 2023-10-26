#include "CWeaponLib.h"

CWeaponLib::CWeaponLib() {}

CWeapon* CWeaponLib::FindWeapon(std::string weaponName) {
	for (auto t : weaponList) {
		if (t->weaponName == weaponName) {
			return t;
		}
	}

	return nullptr;
}

void CWeaponLib::InitAttachment()
{
	Muzzle_None = CMuzzle("Muzzle_None", 0.0f);
	AR_COMP = CMuzzle("AR_COMP", 0.2f);
	AR_LOWFIRE = CMuzzle("AR_LOWFIRE", 0.1f);
	AR_LOWSOUND = CMuzzle("AR_LOWSOUND", 0);
	SMG_COMP = CMuzzle("SMG_COMP", 0.2f);
	SMG_LOWFIRE = CMuzzle("SMG_LOWFIRE", 0.1f);
	SMG_LOWSOUND = CMuzzle("SMG_LOWSOUND", 0);
	SNIPER_COMP = CMuzzle("SNIPER_COMP", 0.2f);
	SNIPER_LOWFIRE = CMuzzle("SNIPER_LOWFIRE", 0.1f);
	SNIPER_LOWSOUND = CMuzzle("SNIPER_LOWSOUND", 0);

	Grip_None = CGrip("Grip_None", 0.0f);
	Angled = CGrip("Angled", 0);
	Half = CGrip("Half", 0.08f);
	Laser = CGrip("Laser", 0);
	LightWeight = CGrip("LightWeight", 0);
	Thumb = CGrip("Thumb", 0.08f);
	Vertical = CGrip("Vertical", 0.15f);

	Magazine_None = CMagazine("Magazine_None", 37);
	SMG = CMagazine("SMG", 37);
	SMG_QUICK = CMagazine("SMG_QUICK", 35);
	AR = CMagazine("AR", 42);
	AR_QUICK = CMagazine("AR_QUICK", 40);
	SNIPER = CMagazine("SNIPER", 8);
	SNIPER_QUICK = CMagazine("SNIPER_QUICK", 7);

	Stock_None = CStock("Stock_None", 0.0f);
	Tactical = CStock("Tactical", 0);
	BulletLoop = CStock("BulletLoop", 0);
	CheekPad = CStock("CheekPad", 0.2f);
	Folding = CStock("Folding", 0.2f);
	Heavy = CStock("Heavy", 0.05f);

	Scope_None = CScope("Scope_None", 0, 1.0f);
	Scope_1 = CScope("Scope_1", 1, 1.0f);
	Scope_2 = CScope("Scope_2", 2, 2.0f);
	Scope_3 = CScope("Scope_3", 3, 3.0f);
	Scope_4 = CScope("Scope_4", 4, 4.0f);
	Scope_6 = CScope("Scope_6", 6, 6.0f);
	Scope_8 = CScope("Scope_8", 8, 8.0f);


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

void CWeaponLib::InitWeapon()
{
	None = CWeapon("WNone");
	Default = CWeapon("Default");
	Mk47_Mutant = CWeapon("Mk47 Mutant");
	AKM = CWeapon("AKM");
	Groza = CWeapon("Groza");
	Beryl_M762 = CWeapon("Beryl M762");
	ACE32 = CWeapon("ACE32");
	M16A4 = CWeapon("M16A4");
	QBZ = CWeapon("QBZ");
	SCAR_L = CWeapon("SCAR-L");
	AUG = CWeapon("AUG");
	G36C = CWeapon("G36C");
	K2 = CWeapon("K2");
	M416 = CWeapon("M416");
	FAMAS = CWeapon("FAMAS");
	DP_28 = CWeapon("DP-28");
	M249 = CWeapon("M249");
	Mk14 = CWeapon("Mk14");
	SLR = CWeapon("SLR");
	SKS = CWeapon("SKS");
	Mk12 = CWeapon("Mk12");
	Mini14 = CWeapon("Mini14");
	QBU = CWeapon("QBU");
	VSS = CWeapon("VSS");
	Lynx_AMR = CWeapon("Lynx AMR");
	AWM = CWeapon("AWM");
	Kar98k = CWeapon("Kar98k");
	Mosin_Nagant = CWeapon("Mosin Nagant");
	M24 = CWeapon("M24");
	Win94 = CWeapon("Win94");
	UMP45 = CWeapon("UMP45");
	Tommy_Gun = CWeapon("Tommy Gun");
	PP_19_Bizon = CWeapon("PP-19 Bizon");
	P90 = CWeapon("P90");
	MP5K = CWeapon("MP5K");
	MP9 = CWeapon("MP9");
	Vector = CWeapon("Vector");
	Micro_UZI = CWeapon("Micro UZI");
	DBS = CWeapon("DBS");
	S1897 = CWeapon("S1897");
	S686 = CWeapon("S686");
	S12K = CWeapon("S12K");
	Sawed_Off = CWeapon("Sawed Off");
	O1R452 = CWeapon("O1R452");
	R1895 = CWeapon("R1895");
	Deagle = CWeapon("Deagle");
	P1911 = CWeapon("P1911");
	P92 = CWeapon("P92");
	P18C = CWeapon("P18C");
	Skorpion = CWeapon("Skorpion");
	MG3_660_RPM = CWeapon("MG3");
	Dragunov = CWeapon("Dragunov");


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
	weaponList.push_back(&Mk14);
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


	//设置后坐力比例表
	Beryl_M762.SetShotInterval(80);
	Beryl_M762.SetRecoilBase(400);
	Beryl_M762.SetRecoilRates({
		1.00,0.82,1.10,1.29,1.03,1.46,1.25,1.38,1.54,1.62,1.82,1.99,2.17,2.31,2.23,2.95,2.65,2.96,3.07,3.89,3.32,3.40,3.43,4.30,3.77,3.21,3.01,2.93,2.92,2.49,2.77,2.23,2.19,2.41,1.94,1.79,1.70,1.98,1.69,1.70,1.70 });


	for (auto t : weaponList) {
		weaponNameList.push_back(t->weaponName);
	}


}

CMuzzle* CWeaponLib::FindMuzzle(string name) {
	for (auto t : muzzleList) {
		if (t->name == name) {
			return t;
		}
	}
	return nullptr;
}

CGrip* CWeaponLib::FindGrip(string name) {
	for (auto t : gripList) {
		if (t->name == name) {
			return t;
		}
	}
	return nullptr;
}

CStock* CWeaponLib::FindStock(string name) {
	for (auto t : stockList) {
		if (t->name == name) {
			return t;
		}
	}
	return nullptr;
}

CScope* CWeaponLib::FindCScope(int scope) {
	for (auto t : scopeList) {
		if (t->scope == scope) {
			return t;
		}
	}
	return nullptr;
}

int CWeaponLib::FindWeaponPosition(std::string weaponName) {
	for (int i = 0; i < weaponNameList.size(); i++) {
		if (weaponNameList[i] == weaponName) {
			return i;
		}
	}

	return -1;
}