#pragma once

#include "resource.h"
struct KeyBoard_State {
    int isLeftContrlPress = 0;
    int isLeftShiftPress = 0;
    int isRightShiftPress = 0;
    int isLeftAltPress = 0;
    int isNum1Press = 0;
    int isNum2Press = 0;
    int isNum3Press = 0;
    int isNum4Press = 0;
    int capsLock = 0;
    int isCapsLockPress = 0;
    int scrollLock = 0;
    int canFocus = FALSE;
};

struct Mouse_State {
    int isRightButtonPress = 0;
    int isLeftButtonPress = 0;
    int continuousTap = FALSE;
    int isStartContinuousTap = FALSE;
    int count = 0;
};

#define IDB_ONE     3301
#define IDB_TWO     3302
#define IDB_LIST1     3303
#define WM_CUSTOM_MESSAGE_PICK_WEAPON       (WM_APP + 0x0001)
#define WM_CUSTOM_MESSAGE                   (WM_APP + 0x0002)