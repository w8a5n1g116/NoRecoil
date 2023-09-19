#include "CFunction1.h"

void CFunction1::Move()
{
	for (int i = 0; i < CurrentWeapon->offset.size(); i++) {
		mouse_event(MOUSEEVENTF_MOVE, 0, CurrentWeapon->ComputeXOffset(CurrentWeapon->offset[i]), 0, 0);
		Sleep(CurrentWeapon->interval);
	}
	
}
