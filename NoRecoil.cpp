// NoRecoil.cpp : 定义应用程序的入口点。
//

#include "framework.h"
#include "NoRecoil.h"
#include <Unknwn.h>
//#include <gdiplus.h>
//#pragma comment(lib,"Gdiplus.lib")
#include "GameStart.h"
//#include "ScreenShot.hpp"

#define MAX_LOADSTRING 100



// 全局变量:
HINSTANCE hInst;                                // 当前实例
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名
HWND hWnd;
HWND hMessageWnd;

// 此代码模块中包含的函数的前向声明:
ATOM                MyRegisterClass(HINSTANCE hInstance);
ATOM                MyRegisterClass2(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK    WndProc2(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

//StaticText Style
DWORD StaticTextStyle = SS_CENTER  | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE;
//键盘钩子
HHOOK keyboardHook;
//鼠标钩子
HHOOK mouseHook;
//句柄
HWND hStaticText;
HWND hStaticText2;
HWND hStaticText3;
HWND hStaticText4;
HWND hStaticText5;
HWND hStaticText6;
HWND hStaticText7;
HWND hStaticText8;
HWND hStaticText9;
HWND hStaticText10;
HWND hMessageText;
HWND hMessageText2;
HWND hMessageText3;
HWND hMessageText4;
HWND hMessageText5;
HWND hMessageText6;
HWND hMessageText7;
HWND hMessageText8;
HWND hMessageText9;
HWND hMessageText10;
HWND hButton;
HWND hButton2;
HWND hButton3;
HWND hComboBox1;
HWND hComboBox2;
HWND hComboBox3;
HWND hComboBox4;
HWND hComboBox5;
HWND hComboBox6;
HWND hComboBox7;
HWND hComboBox8;
HWND hInput0;
HWND hInput1;

HANDLE m_hThread;
UINT m_ThreadId;

LONG volatile m_IsShouldThreadFinish{ FALSE };
LONG volatile startFalg{ TRUE };
unsigned __stdcall ThreadProc(void* mouseState);



//
void Init();
LRESULT CALLBACK LowLevelMouseProc(
    _In_ int    nCode,
    _In_ WPARAM wParam,
    _In_ LPARAM lParam
);
LRESULT CALLBACK LowLevelKeyboardProc(
    _In_ int    nCode,
    _In_ WPARAM wParam,
    _In_ LPARAM lParam
);

HANDLE StartProcessThread();
void SetMessage();


/////////////////////////////////
GameStart gameStart;


void Init()
{

    short key = GetKeyState(VK_CAPITAL);
    gameStart.keyboardState.capsLock = key & 0x0001;

    key = GetKeyState(VK_SCROLL);
    gameStart.keyboardState.scrollLock = key & 0x0001;

    gameStart.InitWeapon();

    if (gameStart.crouchKey == 0x43) { //C
        ComboBox_SelectString(hComboBox1, -1, L"C");
    }
    else if (gameStart.crouchKey == VK_LSHIFT) {
        ComboBox_SelectString(hComboBox1, -1, L"左SHIFT");
    }
    else if (gameStart.crouchKey == VK_LCONTROL) {
        ComboBox_SelectString(hComboBox1, -1, L"左CTRL");
    }

    if (gameStart.proneKey == 0x5A) { //Z
        ComboBox_SelectString(hComboBox2, -1, L"Z");
    }
    else if (gameStart.proneKey == VK_CAPITAL) {
        ComboBox_SelectString(hComboBox2, -1, L"CapsLock");
    }
    else if (gameStart.proneKey == VK_LSHIFT) {
        ComboBox_SelectString(hComboBox2, -1, L"左SHIFT");
    }
    else if (gameStart.proneKey == VK_LCONTROL) {
        ComboBox_SelectString(hComboBox2, -1, L"左CTRL");
    }

    if (gameStart.focusKey == VK_LMENU) {
        ComboBox_SelectString(hComboBox3, -1, L"左ALT");
    }
    else if (gameStart.focusKey == VK_CAPITAL) {
        ComboBox_SelectString(hComboBox3, -1, L"CapsLock");
    }
    else if (gameStart.focusKey == VK_LSHIFT) {
        ComboBox_SelectString(hComboBox3, -1, L"左SHIFT");
    }
    else if (gameStart.focusKey == VK_LCONTROL) {
        ComboBox_SelectString(hComboBox3, -1, L"左CTRL");
    }

    if (gameStart.holdBreathKey == VK_LMENU) {
        ComboBox_SelectString(hComboBox4, -1, L"左ALT");
    }
    else if (gameStart.holdBreathKey == VK_CAPITAL) {
        ComboBox_SelectString(hComboBox4, -1, L"CapsLock");
    }
    else if (gameStart.holdBreathKey == VK_LSHIFT) {
        ComboBox_SelectString(hComboBox4, -1, L"左SHIFT");
    }
    else if (gameStart.holdBreathKey == VK_LCONTROL) {
        ComboBox_SelectString(hComboBox4, -1, L"左CTRL");
    }

    if (GameStart::RESOLUTION_TYPE == 0) {
        ComboBox_SelectString(hComboBox5, -1, L"1440P 全屏模式");
    }
    else if (GameStart::RESOLUTION_TYPE == 1) {
        ComboBox_SelectString(hComboBox5, -1, L"1440P 无边框 125%缩放");
    }
    else if (GameStart::RESOLUTION_TYPE == 2) {
        ComboBox_SelectString(hComboBox5, -1, L"1080P 全屏模式");
    }

    if (GameStart::SWITCH_CROUCH == 0) {
        ComboBox_SelectString(hComboBox6, -1, L"否");
    }
    else if (GameStart::SWITCH_CROUCH == 1) {
        ComboBox_SelectString(hComboBox6, -1, L"是");
    }

    if (GameStart::SWITCH_PRONE == 0) {
        ComboBox_SelectString(hComboBox7, -1, L"否");
    }
    else if (GameStart::SWITCH_PRONE == 1) {
        ComboBox_SelectString(hComboBox7, -1, L"是");
    }

    if (GameStart::SWITCH_ADS == 0) {
        ComboBox_SelectString(hComboBox8, -1, L"否");
    }
    else if (GameStart::SWITCH_ADS == 1) {
        ComboBox_SelectString(hComboBox8, -1, L"是");
    }

    Edit_SetText(hInput0, to_wstring(GameStart::SENSITIVE).c_str());

    SetMessage();


    //设置鼠标钩子`
    mouseHook = SetWindowsHookEx(WH_MOUSE_LL, LowLevelMouseProc, GetModuleHandle(NULL), 0);
    //设置键盘钩子
    keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, GetModuleHandle(NULL), 0);
    StartProcessThread();
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 在此处放置代码。

    // 初始化全局字符串
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_NORECOIL, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);
    MyRegisterClass2(hInstance);

    // 执行应用程序初始化:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_NORECOIL));

    MSG msg;

    // 主消息循环:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int)msg.wParam;
}



//
//  函数: MyRegisterClass()
//
//  目标: 注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_NORECOIL));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;//MAKEINTRESOURCEW(IDC_NORECOIL);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//  函数: MyRegisterClass2()
//
//  目标: 注册窗口类。
//
ATOM MyRegisterClass2(HINSTANCE hInstance) {
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc2;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_NORECOIL));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);//(HBRUSH)CreateSolidBrush(0x000000);//
    wcex.lpszMenuName = NULL;//MAKEINTRESOURCEW(IDC_CONTROLLEGENDWIN32);
    wcex.lpszClassName = L"Message";
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}


//
//   函数: InitInstance(HINSTANCE, int)
//
//   目标: 保存实例句柄并创建主窗口
//
//   注释:
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // 将实例句柄存储在全局变量中

    hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, 460, 365, nullptr, nullptr, hInstance, nullptr);

    int screenWidth = GetSystemMetrics(SM_CXFULLSCREEN);

    hMessageWnd = CreateWindowEx(WS_EX_LAYERED,L"Message", L"", WS_BORDER,//WS_POPUP,WS_BORDER | WS_SIZEBOX
        screenWidth - 300, 10, 200, 180, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    //窗口置顶
    SetWindowPos(hMessageWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
    SetLayeredWindowAttributes(hMessageWnd, 0, 60, LWA_ALPHA);
    UpdateWindow(hMessageWnd);
    

    //SetWindowLong(hMessageWnd, GWL_EXSTYLE, GetWindowLong(hMessageWnd, GWL_EXSTYLE) | WS_EX_LAYERED | WS_EX_TRANSPARENT);
    UpdateWindow(hMessageWnd);

    //业务开始

    Init();

    return TRUE;
}

//最小化到托盘
void ToTray(HWND hWnd)
{
    NOTIFYICONDATA nid;
    nid.cbSize = (DWORD)sizeof(NOTIFYICONDATA);
    nid.hWnd = hWnd;
    nid.uID = IDR_MAINFRAME;
    nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
    nid.uCallbackMessage = WM_TO_TRAY;//自定义的消息 处理托盘图标事件
    nid.hIcon = LoadIcon(GetModuleHandle(0), MAKEINTRESOURCE(IDI_SMALL));
    wcscpy_s(nid.szTip, _T("NoRecoil"));//鼠标放在托盘图标上时显示的文字
    Shell_NotifyIcon(NIM_ADD, &nid);//在托盘区添加图标
}

//关闭时删除托盘图标
void DeleteTray(HWND hWnd)
{
    NOTIFYICONDATA nid;
    nid.cbSize = (DWORD)sizeof(NOTIFYICONDATA);
    nid.hWnd = hWnd;
    nid.uID = IDR_MAINFRAME;
    nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
    nid.uCallbackMessage = WM_TO_TRAY;//自定义的消息名称 处理托盘图标事件
    nid.hIcon = LoadIcon(GetModuleHandle(0), MAKEINTRESOURCE(IDI_SMALL));
    wcscpy_s(nid.szTip, _T("NoRecoil"));//鼠标放在托盘图标上时显示的文字
    Shell_NotifyIcon(NIM_DELETE, &nid);//在托盘中删除图标
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目标: 处理主窗口的消息。
//
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
    {
       
        
        hButton = CreateWindow(L"Button", L"STOP", StaticTextStyle, 30, 10, 180, 40, hWnd, (HMENU)IDB_ONE, hInst, NULL);

        hButton2 = CreateWindow(L"Button", L"应用", StaticTextStyle, 240, 10, 80, 40, hWnd, (HMENU)IDB_TWO, hInst, NULL);

        hButton3 = CreateWindow(L"Button", L"调试", StaticTextStyle, 340, 10, 80, 40, hWnd, (HMENU)IDB_THREE, hInst, NULL);

        
        hStaticText = CreateWindow(L"Static", L"下蹲按键", StaticTextStyle, 30, 55, 180, 20, hWnd, NULL, hInst, NULL);
        hComboBox1 = CreateWindow(L"ComboBox", L"", CBS_DROPDOWNLIST | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE, 30, 80, 180, 100, hWnd, (HMENU)IDB_COMBOBOX1, hInst, NULL);
        ComboBox_AddString(hComboBox1, L"C");
        ComboBox_SetItemData(hComboBox1, 0, 0x43);
        ComboBox_AddString(hComboBox1, L"左SHIFT");
        ComboBox_SetItemData(hComboBox1, 1, VK_LSHIFT);
        ComboBox_AddString(hComboBox1, L"左CTRL");
        ComboBox_SetItemData(hComboBox1, 2, VK_LCONTROL);
        
        hStaticText2 = CreateWindow(L"Static", L"卧倒按键", StaticTextStyle, 30, 110, 180, 20, hWnd, NULL, hInst, NULL);
        hComboBox2 = CreateWindow(L"ComboBox", L"", CBS_DROPDOWNLIST | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE, 30, 135, 180, 100, hWnd, (HMENU)IDB_COMBOBOX2, hInst, NULL);
        ComboBox_AddString(hComboBox2, L"Z");
        ComboBox_SetItemData(hComboBox2, 0, 0x5A);
        ComboBox_AddString(hComboBox2, L"CapsLock");
        ComboBox_SetItemData(hComboBox2, 1, VK_CAPITAL);
        ComboBox_AddString(hComboBox2, L"左SHIFT");
        ComboBox_SetItemData(hComboBox2, 2, VK_LSHIFT);
        ComboBox_AddString(hComboBox2, L"左CTRL");
        ComboBox_SetItemData(hComboBox2, 3, VK_LCONTROL);

        hStaticText3 = CreateWindow(L"Static", L"腰射按键", StaticTextStyle, 30, 165, 180, 20, hWnd, NULL, hInst, NULL);
        hComboBox3 = CreateWindow(L"ComboBox", L"", CBS_DROPDOWNLIST | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE, 30, 190, 180, 100, hWnd, (HMENU)IDB_COMBOBOX3, hInst, NULL);
        ComboBox_AddString(hComboBox3, L"左ALT");
        ComboBox_SetItemData(hComboBox3, 0, 0x5A);
        ComboBox_AddString(hComboBox3, L"CapsLock");
        ComboBox_SetItemData(hComboBox3, 1, VK_CAPITAL);
        ComboBox_AddString(hComboBox3, L"左SHIFT");
        ComboBox_SetItemData(hComboBox3, 2, VK_LSHIFT);
        ComboBox_AddString(hComboBox3, L"左CTRL");
        ComboBox_SetItemData(hComboBox3, 3, VK_LCONTROL);

        hStaticText4 = CreateWindow(L"Static", L"屏息按键", StaticTextStyle, 30, 220, 180, 20, hWnd, NULL, hInst, NULL);
        hComboBox4 = CreateWindow(L"ComboBox", L"", CBS_DROPDOWNLIST | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE, 30, 245, 180, 100, hWnd, (HMENU)IDB_COMBOBOX4, hInst, NULL);
        ComboBox_AddString(hComboBox4, L"左ALT");
        ComboBox_SetItemData(hComboBox4, 0, 0x5A);
        ComboBox_AddString(hComboBox4, L"CapsLock");
        ComboBox_SetItemData(hComboBox4, 1, VK_CAPITAL);
        ComboBox_AddString(hComboBox4, L"左SHIFT");
        ComboBox_SetItemData(hComboBox4, 2, VK_LSHIFT);
        ComboBox_AddString(hComboBox4, L"左CTRL");
        ComboBox_SetItemData(hComboBox4, 3, VK_LCONTROL);

        

        hStaticText7 = CreateWindow(L"Static", L"切换下蹲", StaticTextStyle, 240, 55, 180, 20, hWnd, NULL, hInst, NULL);
        hComboBox6 = CreateWindow(L"ComboBox", L"", CBS_DROPDOWNLIST | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE, 240, 80, 180, 100, hWnd, (HMENU)IDB_COMBOBOX6, hInst, NULL);
        ComboBox_AddString(hComboBox6, L"否");
        ComboBox_SetItemData(hComboBox6, 0, 0);
        ComboBox_AddString(hComboBox6, L"是");
        ComboBox_SetItemData(hComboBox6, 1, 1);

        hStaticText8 = CreateWindow(L"Static", L"切换卧倒", StaticTextStyle, 240, 110, 180, 20, hWnd, NULL, hInst, NULL);
        hComboBox7 = CreateWindow(L"ComboBox", L"", CBS_DROPDOWNLIST | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE, 240, 135, 180, 100, hWnd, (HMENU)IDB_COMBOBOX7, hInst, NULL);
        ComboBox_AddString(hComboBox7, L"否");
        ComboBox_SetItemData(hComboBox7, 0, 0);
        ComboBox_AddString(hComboBox7, L"是");
        ComboBox_SetItemData(hComboBox7, 1, 1);

        hStaticText9 = CreateWindow(L"Static", L"切换开镜", StaticTextStyle, 240, 165, 180, 20, hWnd, NULL, hInst, NULL);
        hComboBox8 = CreateWindow(L"ComboBox", L"", CBS_DROPDOWNLIST | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE, 240, 190, 180, 100, hWnd, (HMENU)IDB_COMBOBOX8, hInst, NULL);
        ComboBox_AddString(hComboBox8, L"否");
        ComboBox_SetItemData(hComboBox8, 0, 0);
        ComboBox_AddString(hComboBox8, L"是");
        ComboBox_SetItemData(hComboBox8, 1, 1);


        hStaticText5 = CreateWindow(L"Static", L"分辨率", StaticTextStyle, 240, 220, 180, 20, hWnd, NULL, hInst, NULL);
        hComboBox5 = CreateWindow(L"ComboBox", L"", CBS_DROPDOWNLIST | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE, 240, 245, 180, 100, hWnd, (HMENU)IDB_COMBOBOX5, hInst, NULL);
        ComboBox_AddString(hComboBox5, L"1440P 全屏模式");
        ComboBox_SetItemData(hComboBox5, 0, 0);
        ComboBox_AddString(hComboBox5, L"1440P 无边框 125%缩放");
        ComboBox_SetItemData(hComboBox5, 1, 1);
        ComboBox_AddString(hComboBox5, L"1080P 全屏模式");
        ComboBox_SetItemData(hComboBox5, 2, 2);

        hStaticText6 = CreateWindow(L"Static", L"开镜灵敏度", StaticTextStyle, 30, 275, 180, 20, hWnd, NULL, hInst, NULL);
        hInput0 = CreateWindow(L"EDIT", L"50", ES_CENTER | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE, 30, 300, 180, 20, hWnd, (HMENU)NULL, hInst, NULL);

        hStaticText10 = CreateWindow(L"Static", L"腰射灵敏度", StaticTextStyle, 240, 275, 180, 20, hWnd, NULL, hInst, NULL);
        hInput1 = CreateWindow(L"EDIT", L"50", ES_CENTER | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE, 240, 300, 180, 20, hWnd, (HMENU)NULL, hInst, NULL);
        
        
    }
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        int a = 0;
        // 分析菜单选择:
        switch (wmId)
        {
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        case IDB_ONE:
            switch (HIWORD(wParam)) {
            case BN_CLICKED:
            {
                if (startFalg == FALSE) {
                    startFalg = TRUE;
                    Button_SetText(hButton,L"STOP");
                }                 
                else {
                    startFalg = FALSE;
                    Button_SetText(hButton, L"START");
                }
                    
            }
            }
            break;
        case IDB_TWO: 
            switch (HIWORD(wParam)) {
            case BN_CLICKED:
            {
                gameStart.InitWeapon();

                wchar_t buff[1024];
                Edit_GetText(hInput0, buff, 1024);
                int sens = _wtoi(buff);
                gameStart.SetSensitive(sens);
              
            }
            }
            break;
        case IDB_THREE:
            switch (HIWORD(wParam)) {
            case BN_CLICKED:
            {
                if (!gameStart.debug) {
                    ShowWindow(hMessageWnd, SW_SHOW);
                    gameStart.debug = true;
                }
                else {
                    ShowWindow(hMessageWnd, SW_HIDE);
                    gameStart.debug = false;
                }

            }
            }
            break;
        case IDB_COMBOBOX1:
            switch (HIWORD(wParam)) {
            case CBN_SELCHANGE:
            {
                int index = ComboBox_GetCurSel(hComboBox1);
                unsigned short key = ComboBox_GetItemData(hComboBox1, index);
                gameStart.SetCrouchKey(key);
            }
            }
            break;
        case IDB_COMBOBOX2:
            switch (HIWORD(wParam)) {
            case CBN_SELCHANGE:
            {
                int index = ComboBox_GetCurSel(hComboBox2);
                unsigned short key = ComboBox_GetItemData(hComboBox2, index);
                gameStart.SetProneKey(key);
            }
            }
            break;
        case IDB_COMBOBOX3:
            switch (HIWORD(wParam)) {
            case CBN_SELCHANGE:
            {
                int index = ComboBox_GetCurSel(hComboBox3);
                unsigned short key = ComboBox_GetItemData(hComboBox3, index);
                gameStart.SetFocusKey(key);
            }
            }
            break;
        case IDB_COMBOBOX4:
            switch (HIWORD(wParam)) {
            case CBN_SELCHANGE:
            {
                int index = ComboBox_GetCurSel(hComboBox4);
                unsigned short key = ComboBox_GetItemData(hComboBox4, index);
                gameStart.SetHoldBreathKey(key);
            }
            }
            break;
        case IDB_COMBOBOX5:
            switch (HIWORD(wParam)) {
            case CBN_SELCHANGE:
            {
                int index = ComboBox_GetCurSel(hComboBox5);
                int resolution = ComboBox_GetItemData(hComboBox5, index);
                gameStart.SelectResolution(resolution);
            }
            }
            break;
        case IDB_COMBOBOX6:
            switch (HIWORD(wParam)) {
            case CBN_SELCHANGE:
            {
                int index = ComboBox_GetCurSel(hComboBox6);
                int value = ComboBox_GetItemData(hComboBox6, index);
                gameStart.SetSwitchCrouch(value);
            }
            }
            break;
        case IDB_COMBOBOX7:
            switch (HIWORD(wParam)) {
            case CBN_SELCHANGE:
            {
                int index = ComboBox_GetCurSel(hComboBox7);
                int value = ComboBox_GetItemData(hComboBox7, index);
                gameStart.SetSwitcProne(value);
            }
            }
            break;
        case IDB_COMBOBOX8:
            switch (HIWORD(wParam)) {
            case CBN_SELCHANGE:
            {
                int index = ComboBox_GetCurSel(hComboBox8);
                int value = ComboBox_GetItemData(hComboBox8, index);
                gameStart.SetSwitcADS(value);
            }
            }
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: 在此处添加使用 hdc 的任何绘图代码...
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_SIZE:
    {
        if (wParam == SIZE_MINIMIZED) {
            ToTray(hWnd);
            ShowWindow(hWnd, SW_HIDE);
        }
    }
    break;
    case WM_DESTROY:
        m_IsShouldThreadFinish = TRUE;
        DeleteTray(hWnd);
        PostQuitMessage(0);
        break;    
    case WM_CUSTOM_MESSAGE_PICK_WEAPON:
        //ListBox_SetCurSel(hList1, wParam);
        
        SetMessage();
        break;
    case WM_TO_TRAY: 
    {
        if (lParam == WM_LBUTTONDBLCLK) {
            SetForegroundWindow(hWnd);
            ShowWindow(hWnd, SW_SHOWNORMAL);
        }       
    }     
    break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目标: 处理主窗口的消息。
//
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc2(HWND hMWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
    {
        hMessageText = CreateWindow(L"Static", L"", StaticTextStyle, 0, 0, 185, 30, hMWnd, NULL, hInst, NULL);
        hMessageText2 = CreateWindow(L"Static", L"", StaticTextStyle, 0, 30, 95, 20, hMWnd, NULL, hInst, NULL);
        hMessageText3 = CreateWindow(L"Static", L"", StaticTextStyle, 95, 30, 90, 20, hMWnd, NULL, hInst, NULL);
        hMessageText4 = CreateWindow(L"Static", L"", StaticTextStyle, 0, 50, 60, 25, hMWnd, NULL, hInst, NULL);
        hMessageText5 = CreateWindow(L"Static", L"", StaticTextStyle, 60, 50, 60, 25, hMWnd, NULL, hInst, NULL);
        hMessageText6 = CreateWindow(L"Static", L"", StaticTextStyle, 120, 50, 60, 25, hMWnd, NULL, hInst, NULL);
        hMessageText7 = CreateWindow(L"Static", L"", StaticTextStyle, 0, 80, 95, 25, hMWnd, NULL, hInst, NULL);
        hMessageText8 = CreateWindow(L"Static", L"", StaticTextStyle, 95, 80, 95, 25, hMWnd, NULL, hInst, NULL);
        hMessageText9 = CreateWindow(L"Static", L"", StaticTextStyle, 0, 110, 95, 25, hMWnd, NULL, hInst, NULL);
        hMessageText10 = CreateWindow(L"Static", L"", StaticTextStyle, 95, 110, 95, 25, hMWnd, NULL, hInst, NULL);

        LOGFONT font;
        font.lfHeight = 32;
        font.lfWidth = 0;
        font.lfEscapement = 0;
        font.lfOrientation = 0;
        font.lfWeight = FW_BOLD;
        font.lfItalic = true;
        font.lfUnderline = false;
        font.lfStrikeOut = false;
        font.lfEscapement = 0;
        font.lfOrientation = 0;
        font.lfOutPrecision = OUT_DEFAULT_PRECIS;
        font.lfClipPrecision = CLIP_STROKE_PRECIS | CLIP_MASK | CLIP_TT_ALWAYS | CLIP_LH_ANGLES;
        font.lfQuality = ANTIALIASED_QUALITY;
        font.lfPitchAndFamily = VARIABLE_PITCH | FF_DONTCARE;

        HFONT hFont = ::CreateFontIndirect(&font);
        SendMessage(hMessageText, WM_SETFONT, (WPARAM)hFont, TRUE);

    }
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        int a = 0;
        // 分析菜单选择:
        switch (wmId)
        {           
        default:
            return DefWindowProc(hMWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hMWnd, &ps);
        // TODO: 在此处添加使用 hdc 的任何绘图代码...
        EndPaint(hMWnd, &ps);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_CUSTOM_MESSAGE:
        
        break;
    default:
        return DefWindowProc(hMWnd, message, wParam, lParam);
    }
    return 0;
}

// “关于”框的消息处理程序。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}



LRESULT CALLBACK LowLevelMouseProc(
    _In_ int    nCode,
    _In_ WPARAM wParam,
    _In_ LPARAM lParam
)
{
    if (nCode < 0) {
        return CallNextHookEx(NULL, nCode, wParam, lParam);
    }
    MSLLHOOKSTRUCT* msllhook = reinterpret_cast<MSLLHOOKSTRUCT*>(lParam);

    gameStart.DoMouseEvent(wParam,HIWORD(msllhook->mouseData));

    return 0;
}

LRESULT CALLBACK LowLevelKeyboardProc(
    _In_ int    nCode,
    _In_ WPARAM wParam,
    _In_ LPARAM lParam
)
{
    if (nCode < 0) {
        return CallNextHookEx(NULL, nCode, wParam, lParam);
    }
    tagKBDLLHOOKSTRUCT* kbhook = reinterpret_cast<tagKBDLLHOOKSTRUCT*>(lParam);
    if (wParam == WM_KEYDOWN) {
        gameStart.DoKeyBoardEvent(kbhook->vkCode,1);
        
    }else if (wParam == WM_KEYUP) {
        gameStart.DoKeyBoardEvent(kbhook->vkCode, 0);
    }else if (wParam == WM_SYSKEYDOWN) {
        gameStart.DoKeyBoardEvent(kbhook->vkCode, 1);       
    }else if (wParam == WM_SYSKEYUP) {
        gameStart.DoKeyBoardEvent(kbhook->vkCode, 0);      
    }
    return 0;
}



HANDLE StartProcessThread() {
    m_hThread = (HANDLE)_beginthreadex(NULL, 0, &ThreadProc, NULL, 0, &m_ThreadId);
    return HANDLE();
}


unsigned __stdcall ThreadProc(void* o) {
    //Mouse_State* state = (Mouse_State*)mouseState;
    while (m_IsShouldThreadFinish == FALSE) {
        if (startFalg == TRUE) {
            gameStart.Move();
        }
    }
    _endthreadex(0);
    return 0;
}








void SetMessage() {
    char lmessage[1024];
    sprintf_s(lmessage, 1024, "%s", gameStart.CurrentWeapon->weaponName.c_str());
    SetWindowTextA(hMessageText, lmessage);
    sprintf_s(lmessage, 1024, "%d",  gameStart.CurrentWeapon->scope != NULL ? gameStart.CurrentWeapon->scope->scope : 0);
    SetWindowTextA(hMessageText2, lmessage);
    sprintf_s(lmessage, 1024, "%.2f", gameStart.CurrentWeapon->recoilBaseRunning);
    SetWindowTextA(hMessageText3, lmessage);
    sprintf_s(lmessage, 1024, "%d", gameStart.countPx);
    SetWindowTextA(hMessageText4, lmessage);
    
    sprintf_s(lmessage, 1024, "%d", gameStart.CurrentWeapon->currentShot);
    SetWindowTextA(hMessageText5, lmessage);
    
    int stance = 0;
    if (gameStart.isCrouch) {
        stance = 1;
    }
    if (gameStart.isProne) {
        stance = 2;
    }
    //sprintf_s(lmessage, 1024, "%d", stance);
    sprintf_s(lmessage, 1024, "%.2f-%d", gameStart.CurrentWeapon->attachmentEffect, stance);
    SetWindowTextA(hMessageText6, lmessage);

    sprintf_s(lmessage, 1024, "%s", gameStart.CurrentWeapon->muzzle != NULL ? gameStart.CurrentWeapon->muzzle->name.c_str() : "");
    SetWindowTextA(hMessageText7, lmessage);
    sprintf_s(lmessage, 1024, "%s", gameStart.CurrentWeapon->grip != NULL ? gameStart.CurrentWeapon->grip->name.c_str() : "");
    SetWindowTextA(hMessageText8, lmessage);
    sprintf_s(lmessage, 1024, "%s", gameStart.CurrentWeapon->stock != NULL ? gameStart.CurrentWeapon->stock->name.c_str() : "");
    SetWindowTextA(hMessageText9, lmessage);
    sprintf_s(lmessage, 1024, "%s-%s", gameStart.adsOpened? "ADS" : "",gameStart.packageOpened?"PKG":"");
    SetWindowTextA(hMessageText10, lmessage);
}
