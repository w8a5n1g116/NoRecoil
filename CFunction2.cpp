#include "CFunction2.h"
#include <chrono>

void CFunction2::LoadSetting()
{
    offsetArray_1[0] = &offset_1_1;
    offsetArray_1[1] = &offset_1_2;
    offsetArray_1[2] = &offset_1_3;
    offsetArray_1[3] = &offset_1_4;
    offsetArray_1[4] = &offset_1_6;
    offsetArray_2[0] = &offset_2_1;
    offsetArray_2[1] = &offset_2_2;
    offsetArray_2[2] = &offset_2_3;
    offsetArray_2[3] = &offset_2_4;
    offsetArray_2[4] = &offset_2_6;


    interval = GetPrivateProfileInt(L"General", L"interval", 5, iniFilePath.c_str());
    offset_1_1 = GetPrivateProfileInt(L"General", L"offset_1_1", 10, iniFilePath.c_str());
    offset_1_2 = GetPrivateProfileInt(L"General", L"offset_1_2", 10, iniFilePath.c_str());
    offset_1_3 = GetPrivateProfileInt(L"General", L"offset_1_3", 10, iniFilePath.c_str());
    offset_1_4 = GetPrivateProfileInt(L"General", L"offset_1_4", 10, iniFilePath.c_str());
    offset_1_6 = GetPrivateProfileInt(L"General", L"offset_1_6", 10, iniFilePath.c_str());
    offset_2_1 = GetPrivateProfileInt(L"General", L"offset_2_1", 10, iniFilePath.c_str());
    offset_2_2 = GetPrivateProfileInt(L"General", L"offset_2_2", 10, iniFilePath.c_str());
    offset_2_3 = GetPrivateProfileInt(L"General", L"offset_2_3", 10, iniFilePath.c_str());
    offset_2_4 = GetPrivateProfileInt(L"General", L"offset_2_4", 10, iniFilePath.c_str());
    offset_2_6 = GetPrivateProfileInt(L"General", L"offset_2_6", 10, iniFilePath.c_str());
    offset_0 = GetPrivateProfileInt(L"General", L"offset_0", 10, iniFilePath.c_str());
    single_tap_interval = GetPrivateProfileInt(L"General", L"single_tap_interval", 100, iniFilePath.c_str());
}

void CFunction2::ChangeSetting(int interval, int offset_1_1, int offset_1_2, int offset_1_3, int offset_1_4, int offset_1_6, int offset_2_1, int offset_2_2, int offset_2_3, int offset_2_4, int offset_2_6, int offset_0)
{
    this->interval = interval;
    this->offset_1_1 = offset_1_1;
    this->offset_1_2 = offset_1_2;
    this->offset_1_3 = offset_1_3;
    this->offset_1_4 = offset_1_4;
    this->offset_1_6 = offset_1_6;
    this->offset_2_1 = offset_2_1;
    this->offset_2_2 = offset_2_2;
    this->offset_2_3 = offset_2_3;
    this->offset_2_4 = offset_2_4;
    this->offset_2_6 = offset_2_6;
    this->offset_0 = offset_0;
}



void CFunction2::Move(int capsLock,int scrollLock)
{
    current_offset = capsLock ? *offsetArray_2[profile] : *offsetArray_1[profile];

    if (scrollLock)
    {
        current_offset = capsLock ? offset_2_1 : offset_1_1;
    }

    int y = current_offset;
    mouse_event(MOUSEEVENTF_MOVE, 0, y, 0, 0);
    Delay(interval);
}

void CFunction2::FocusMove()
{
    current_offset_2 = offset_0;
    mouse_event(MOUSEEVENTF_MOVE, 0, current_offset_2, 0, 0);
    Delay(interval);
}

void CFunction2::Delay(int timeout_ms)
{
    auto start = std::chrono::system_clock::now();
    while (true)
    {
        auto duration =
            std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start).count();
        if (duration > timeout_ms)
        {
            break;
        }
    }
}
