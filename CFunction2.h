#pragma once
#include "framework.h"
#include <WinBase.h>
class CFunction2
{public:
    int interval = 10;
    int single_tap_interval = 100;
    int current_offset = 0;
    int current_offset_2 = 0;
    int offset_0 = 1;
    int offset_1_1 = 1;
    int offset_1_2 = 1;
    int offset_1_3 = 1;
    int offset_1_4 = 1;
    int offset_1_6 = 1;
    int offset_2_1 = 1;
    int offset_2_2 = 1;
    int offset_2_3 = 1;
    int offset_2_4 = 1;
    int offset_2_6 = 1;
    int profile = 0;
    int* offsetArray_1[5] = { 0 };
    int* offsetArray_2[5] = { 0 };


    std::wstring GetUserProfilePath() {
        std::wstring path = L"";
        const wchar_t* homeProfile = L"USERPROFILE";
        wchar_t homePath[1024] = { 0 };

        unsigned int pathSize = GetEnvironmentVariable(homeProfile, homePath, 1024);

        if (pathSize == 0 || pathSize > 1024)
        {
            // 获取失败 或者 路径太长 
            int ret = GetLastError();
        }
        else
        {
            path = std::wstring(homePath);
        }
        return path;
    }

    std::wstring iniFilePath = GetUserProfilePath() + L"\\config.ini";


    void LoadSetting();
    void ChangeSetting(int interval, int offset_1_1, int offset_1_2, int offset_1_3, int offset_1_4, int offset_1_6, int offset_2_1, int offset_2_2, int offset_2_3, int offset_2_4, int offset_2_6, int offset_0);
	void Move(int capsLock, int scrollLock);
    void FocusMove();
};

