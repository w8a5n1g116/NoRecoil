#pragma once
#include "CWeapon.h"
#include "CMuzzle.h"
#include "CGrip.h"
#include "CMagazine.h"
#include "CStock.h"
class CWeaponLib
{
public:
	CWeapon AKM = CWeapon("AKM", 94, {
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
		}, 40);

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
};

