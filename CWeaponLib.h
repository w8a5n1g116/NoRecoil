#pragma once
#include "CWeapon.h"
#include "CMuzzle.h"
#include "CGrip.h"
#include "CMagazine.h"
#include "CStock.h"
#include <map>
class CWeaponLib
{
public:
	/*CWeapon AKM = CWeapon("AKM", 94, {
		32,32,32,38,38,
		43,43,43,43,43,
		53,53,53,53,53,
		55,55,55,55,55,
		55,55,55,55,55,
		55,55,55,55,55,
		55,55,55,55,55,
		55,55,55,55,55,
		55,55 }, 42);

	CWeapon ACE32 = CWeapon("ACE32", 77, {
		40,30,30,35,35,
		35,35,45,45,45,
		40,50,50,50,50,
		45,50,55,50,55,
		50,50,55,55,50,
		45,50,60,55,55,
		50,55,55,55,50,
		50,60,55,50,60,
		}, 40);*/

	/*CWeapon ACE32 = CWeapon("ACE32", 77, {
		30,24,25,31,32,
		32,35,44,45,44,
		40,47,48,48,46,
		43,49,55,49,56,
		48,48,52,55,51,
		44,47,57,56,54,
		50,53,53,57,51,
		52,58,54,50,58,
		}, 40);*/

	CWeapon Default		= CWeapon("Default", CWeapon::FUNCTION2, 4, 4);
	CWeapon Mk47_Mutant		= CWeapon("Mk47 Mutant",CWeapon::FUNCTION2, 10, 9);
	CWeapon AKM				= CWeapon("AKM", CWeapon::FUNCTION2, 10, 9);
	CWeapon Groza			= CWeapon("Groza", CWeapon::FUNCTION2, 10, 9);
	CWeapon Beryl_M762		= CWeapon("Beryl M762", CWeapon::FUNCTION2, 10, 9);
	CWeapon ACE32			= CWeapon("ACE32", CWeapon::FUNCTION2, 10, 9);
	CWeapon M16A4			= CWeapon("M16A4", CWeapon::FUNCTION2, 10, 9);
	CWeapon QBZ				= CWeapon("QBZ", CWeapon::FUNCTION2, 10, 9);
	CWeapon SCAR_L			= CWeapon("SCAR-L", CWeapon::FUNCTION2, 10, 9);
	CWeapon AUG				= CWeapon("AUG", CWeapon::FUNCTION2, 10, 9);
	CWeapon G36C			= CWeapon("G36C", CWeapon::FUNCTION2, 10, 9);
	CWeapon K2				= CWeapon("K2", CWeapon::FUNCTION2, 10, 9);
	CWeapon M416			= CWeapon("M416", CWeapon::FUNCTION2, 10, 9);
	CWeapon FAMAS			= CWeapon("FAMAS", CWeapon::FUNCTION2, 10, 9);
	CWeapon DP_28			= CWeapon("DP_28", CWeapon::FUNCTION2, 10, 9);
	CWeapon M249			= CWeapon("M249", CWeapon::FUNCTION2, 10, 9);
	CWeapon Mk14			= CWeapon("Mk14", CWeapon::FUNCTION1, 10, 9);
	CWeapon SLR				= CWeapon("SLR", CWeapon::FUNCTION1, 10, 9);
	CWeapon SKS				= CWeapon("SKS", CWeapon::FUNCTION1, 10, 9);
	CWeapon Mk12			= CWeapon("Mk12", CWeapon::FUNCTION1, 10, 9);
	CWeapon Mini14			= CWeapon("Mini14", CWeapon::FUNCTION1, 10, 9);
	CWeapon QBU				= CWeapon("QBU", CWeapon::FUNCTION1, 10, 9);
	CWeapon VSS				= CWeapon("VSS", CWeapon::FUNCTION2, 10, 9);
	CWeapon Lynx_AMR		= CWeapon("Lynx AMR", CWeapon::FUNCTION1, 10, 9);
	CWeapon AWM				= CWeapon("AWM", CWeapon::FUNCTION1, 10, 9);
	CWeapon Kar98k			= CWeapon("Kar98k", CWeapon::FUNCTION1, 10, 9);
	CWeapon Mosin_Nagant	= CWeapon("Mosin Nagant", CWeapon::FUNCTION1, 10, 9);
	CWeapon M24				= CWeapon("M24", CWeapon::FUNCTION1, 10, 9);
	CWeapon Win94			= CWeapon("Win94", CWeapon::FUNCTION1, 10, 9);
	CWeapon UMP45			= CWeapon("UMP45", CWeapon::FUNCTION2, 10, 9);
	CWeapon Tommy_Gun		= CWeapon("Tommy Gun", CWeapon::FUNCTION2, 10, 9);
	CWeapon PP_19_Bizon		= CWeapon("PP 19 Bizon", CWeapon::FUNCTION2, 10, 9);
	CWeapon P90				= CWeapon("P90", CWeapon::FUNCTION2, 10, 9);
	CWeapon MP5K			= CWeapon("MP5K", CWeapon::FUNCTION2, 10, 9);
	CWeapon MP9				= CWeapon("MP9", CWeapon::FUNCTION2, 10, 9);
	CWeapon Vector			= CWeapon("Vector", CWeapon::FUNCTION2, 10, 9);
	CWeapon Micro_UZI		= CWeapon("Micro UZI", CWeapon::FUNCTION2, 10, 9);
	CWeapon DBS				= CWeapon("DBS", CWeapon::FUNCTION1, 10, 9);
	CWeapon S1897			= CWeapon("S1897", CWeapon::FUNCTION1, 10, 9);
	CWeapon S686			= CWeapon("S686", CWeapon::FUNCTION1, 10, 9);
	CWeapon S12K			= CWeapon("S12K", CWeapon::FUNCTION1, 10, 9);
	CWeapon Sawed_Off		= CWeapon("Sawed Off", CWeapon::FUNCTION1, 10, 9);
	CWeapon O1R452			= CWeapon("O1R452", CWeapon::FUNCTION1, 10, 9);
	CWeapon R1895			= CWeapon("R1895", CWeapon::FUNCTION1, 10, 9);
	CWeapon Deagle			= CWeapon("Deagle", CWeapon::FUNCTION2, 10, 9);
	CWeapon P1911			= CWeapon("P1911", CWeapon::FUNCTION1, 10, 9);
	CWeapon P92				= CWeapon("P92", CWeapon::FUNCTION1, 10, 9);
	CWeapon P18C			= CWeapon("P18C", CWeapon::FUNCTION2, 10, 9);
	CWeapon Skorpion		= CWeapon("Skorpion", CWeapon::FUNCTION2, 10, 9);
	CWeapon MG3_660_RPM		= CWeapon("MG3 660 RPM", CWeapon::FUNCTION2, 10, 9);
	CWeapon MG3_990_RPM		= CWeapon("MG3 990 RPM", CWeapon::FUNCTION2, 10, 9);

	std::map<std::string, CWeapon> weaponMap;

	CMuzzle AR_COMP = CMuzzle(CMuzzle::AR_COMP, 0.2f);
	CMuzzle AR_LOWFIRE = CMuzzle(CMuzzle::AR_LOWFIRE, 0.1f);
	CMuzzle AR_LOWSOUND = CMuzzle(CMuzzle::AR_LOWSOUND, 0);
	CMuzzle SMG_COMP = CMuzzle(CMuzzle::SMG_COMP, 0.2f);
	CMuzzle SMG_LOWFIRE = CMuzzle(CMuzzle::SMG_LOWFIRE, 0.1f);
	CMuzzle SMG_LOWSOUND = CMuzzle(CMuzzle::SMG_LOWSOUND, 0);
	CMuzzle SNIPER_COMP = CMuzzle(CMuzzle::SNIPER_COMP, 0.2f);
	CMuzzle SNIPER_LOWFIRE = CMuzzle(CMuzzle::SNIPER_LOWFIRE, 0.1f);
	CMuzzle SNIPER_LOWSOUND = CMuzzle(CMuzzle::SNIPER_LOWSOUND, 0);

	CGrip Angled = CGrip(CGrip::Angled, 0);
	CGrip Half = CGrip(CGrip::Half, 0.08f);
	CGrip Laser = CGrip(CGrip::Laser, 0);
	CGrip LightWeight = CGrip(CGrip::LightWeight, 0);
	CGrip Thumb = CGrip(CGrip::Thumb, 0.08f);
	CGrip Vertical = CGrip(CGrip::Vertical, 0.15f);

	CMagazine SMG = CMagazine(CMagazine::SMG, 37);
	CMagazine SMG_QUICK = CMagazine(CMagazine::SMG_QUICK, 35);
	CMagazine AR = CMagazine(CMagazine::AR, 42);
	CMagazine AR_QUICK = CMagazine(CMagazine::AR_QUICK, 40);
	CMagazine SNIPER = CMagazine(CMagazine::SNIPER, 8);
	CMagazine SNIPER_QUICK = CMagazine(CMagazine::SNIPER_QUICK, 7);

	CStock Tactical = CStock(CStock::Tactical, 0);
	CStock BulletLoop = CStock(CStock::BulletLoop, 0);
	CStock CheekPad = CStock(CStock::CheekPad, 0.2f);
	CStock Folding = CStock(CStock::Folding, 0.2f);
	CStock Heavy = CStock(CStock::Heavy, 0.05f);

	CWeaponLib() {
		weaponMap.insert(std::make_pair("Default", Default));
		weaponMap.insert(std::make_pair("Mk47 Mutant", Mk47_Mutant));
		weaponMap.insert(std::make_pair("AKM", AKM));
		weaponMap.insert(std::make_pair("Groza", Groza));
		weaponMap.insert(std::make_pair("Beryl M762", Beryl_M762));
		weaponMap.insert(std::make_pair("ACE32", ACE32));
		weaponMap.insert(std::make_pair("M16A4", M16A4));
		weaponMap.insert(std::make_pair("QBZ", QBZ));
		weaponMap.insert(std::make_pair("SCAR-L", SCAR_L));
		weaponMap.insert(std::make_pair("AUG", AUG));
		weaponMap.insert(std::make_pair("G36C", G36C));
		weaponMap.insert(std::make_pair("K2", K2));
		weaponMap.insert(std::make_pair("M416", M416));
		weaponMap.insert(std::make_pair("FAMAS", FAMAS));
		weaponMap.insert(std::make_pair("DP-28", DP_28));
		weaponMap.insert(std::make_pair("M249", M249));
		weaponMap.insert(std::make_pair("Mk14", Mk14));
		weaponMap.insert(std::make_pair("SLR", SLR));
		weaponMap.insert(std::make_pair("SKS", SKS));
		weaponMap.insert(std::make_pair("Mk12", Mk12));
		weaponMap.insert(std::make_pair("Mini14", Mini14));
		weaponMap.insert(std::make_pair("QBU", QBU));
		weaponMap.insert(std::make_pair("VSS", VSS));
		weaponMap.insert(std::make_pair("Lynx AMR", Lynx_AMR));
		weaponMap.insert(std::make_pair("AWM", AWM));
		weaponMap.insert(std::make_pair("Kar98k", Kar98k));
		weaponMap.insert(std::make_pair("Mosin Nagant", Mosin_Nagant));
		weaponMap.insert(std::make_pair("M24", M24));
		weaponMap.insert(std::make_pair("Win94", Win94));
		weaponMap.insert(std::make_pair("UMP45", UMP45));
		weaponMap.insert(std::make_pair("Tommy Gun", Tommy_Gun));
		weaponMap.insert(std::make_pair("PP 19 Bizon", PP_19_Bizon));
		weaponMap.insert(std::make_pair("P90", P90));
		weaponMap.insert(std::make_pair("MP5K", MP5K));
		weaponMap.insert(std::make_pair("MP9", MP9));
		weaponMap.insert(std::make_pair("Vector", Vector));
		weaponMap.insert(std::make_pair("Micro UZI", Micro_UZI));
		weaponMap.insert(std::make_pair("DBS", DBS));
		weaponMap.insert(std::make_pair("S1897", S1897));
		weaponMap.insert(std::make_pair("S686", S686));
		weaponMap.insert(std::make_pair("S12K", S12K));
		weaponMap.insert(std::make_pair("O1R452", O1R452));
		weaponMap.insert(std::make_pair("R1895", R1895));
		weaponMap.insert(std::make_pair("Deagle", Deagle));
		weaponMap.insert(std::make_pair("P1911", P1911));
		weaponMap.insert(std::make_pair("P92", P92));
		weaponMap.insert(std::make_pair("P18C", P18C));
		weaponMap.insert(std::make_pair("Skorpion", Skorpion));
		weaponMap.insert(std::make_pair("MG3 660 RPM", MG3_660_RPM));
		weaponMap.insert(std::make_pair("MG3 990 RPM", MG3_990_RPM));
	}

	CWeapon* FindWeapon(std::string weaponName) {
		auto key_handle = weaponMap.find(weaponName);
		if (key_handle != weaponMap.end()) {
			return &key_handle->second;
		}
		else {
			return nullptr;
		}
	}
};

