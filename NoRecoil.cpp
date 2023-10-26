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
//HWND hStaticText3;
HWND hMessageText;
HWND hMessageText2;
HWND hMessageText3;
HWND hMessageText4;
HWND hMessageText5;
HWND hMessageText6;
HWND hButton;
HWND hButton2;
HWND hComboBox1;
HWND hComboBox2;
HWND hComboBox3;
HWND hComboBox4;
HWND hComboBox5;
HWND hInput0;

HANDLE m_hThread;
UINT m_ThreadId;
HANDLE m_hMatchThread;
UINT m_matchThreadId;

LONG volatile m_IsShouldThreadFinish{ FALSE };
LONG volatile startFalg{ TRUE };
unsigned __stdcall ThreadProc(void* mouseState);
unsigned __stdcall MatchThreadProc(void* o);



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
HANDLE MatchProcessThread();
void SetMessage();

HANDLE m_timerHandle = NULL;
HANDLE m_timerHandle2 = NULL;
HANDLE m_timerHandle3 = NULL;
HANDLE m_timerHandle4 = NULL;

void KeyboardInput(UINT key, BOOL isKeyDown);
void CALLBACK TimerProc(void* key, BOOLEAN TimerOrWaitFired);
void CALLBACK TimerProc2(void* key, BOOLEAN TimerOrWaitFired);
void CALLBACK TimerProc3(void* key, BOOLEAN TimerOrWaitFired);

/////////////////////////////////
GameStart gameStart;


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
        CW_USEDEFAULT, 0, 250, 465, nullptr, nullptr, hInstance, nullptr);

    int screenWidth = GetSystemMetrics(SM_CXFULLSCREEN);

    hMessageWnd = CreateWindowEx(WS_EX_LAYERED,L"Message", L"", WS_BORDER,//WS_POPUP,WS_BORDER | WS_SIZEBOX
        screenWidth - 300, 10, 200, 110, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);


    //窗口置顶
    SetWindowPos(hMessageWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
    SetLayeredWindowAttributes(hMessageWnd, 0, 60, LWA_ALPHA);
    ShowWindow(hMessageWnd, SW_SHOW);
    //UpdateWindow(hMessageWnd);
    

    //SetWindowLong(hMessageWnd, GWL_EXSTYLE, GetWindowLong(hMessageWnd, GWL_EXSTYLE) | WS_EX_LAYERED | WS_EX_TRANSPARENT);
    UpdateWindow(hMessageWnd);

    //业务开始

    Init();

    return TRUE;
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

        hStaticText5 = CreateWindow(L"Static", L"分辨率", StaticTextStyle, 30, 275, 180, 20, hWnd, NULL, hInst, NULL);
        hComboBox5 = CreateWindow(L"ComboBox", L"", CBS_DROPDOWNLIST | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE, 30, 300, 180, 100, hWnd, (HMENU)IDB_COMBOBOX5, hInst, NULL);
        ComboBox_AddString(hComboBox5, L"1440P 全屏模式");
        ComboBox_SetItemData(hComboBox5, 0, 0);
        ComboBox_AddString(hComboBox5, L"1440P 无边框 125%缩放");
        ComboBox_SetItemData(hComboBox5, 1, 1);
        ComboBox_AddString(hComboBox5, L"1080P 全屏模式");
        ComboBox_SetItemData(hComboBox5, 2, 2);

        hStaticText6 = CreateWindow(L"Static", L"开镜灵敏度", StaticTextStyle, 30, 330, 180, 20, hWnd, NULL, hInst, NULL);
        hInput0 = CreateWindow(L"EDIT", L"50", ES_CENTER | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE, 30, 355, 180, 20, hWnd, (HMENU)IDB_COMBOBOX5, hInst, NULL);
        
        hButton2 = CreateWindow(L"Button", L"应用", StaticTextStyle, 30, 380, 180, 40, hWnd, (HMENU)IDB_TWO, hInst, NULL);
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
    case WM_DESTROY:
        m_IsShouldThreadFinish = TRUE;
        PostQuitMessage(0);
        break;
    case WM_CUSTOM_MESSAGE_PICK_WEAPON:
        //ListBox_SetCurSel(hList1, wParam);
        
        SetMessage();
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

void Init()
{

    short key = GetKeyState(VK_CAPITAL);
    gameStart.keyboardState.capsLock = key & 0x0001;

    key = GetKeyState(VK_SCROLL);
    gameStart.keyboardState.scrollLock = key & 0x0001;

    gameStart.InitWeapon();
    
    if (gameStart.crouchKey == 0x43) { //C
        ComboBox_SelectString(hComboBox1, -1,L"C");
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

    Edit_SetText(hInput0, to_wstring(GameStart::SENSITIVE).c_str());

    SetMessage();


    //设置鼠标钩子`
    mouseHook = SetWindowsHookEx(WH_MOUSE_LL, LowLevelMouseProc, GetModuleHandle(NULL), 0);
    //设置键盘钩子
    keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, GetModuleHandle(NULL), 0);
    StartProcessThread();
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

    switch (wParam)
    {
    case WM_LBUTTONDOWN:
        gameStart.mouseState.isLeftButtonPress = 1;
        break;
    case WM_LBUTTONUP:
        gameStart.mouseState.isLeftButtonPress = 0;
        break;
    case WM_RBUTTONDOWN:
        gameStart.mouseState.isRightButtonPress = 1;
        break;
    case WM_RBUTTONUP:
        gameStart.mouseState.isRightButtonPress = 0;
        break;
    }

    if (gameStart.keyboardState.isLeftContrlPress && wParam == WM_MBUTTONDOWN && !gameStart.mouseState.isLeftButtonPress) {
        KeyboardInput(VK_SCROLL, TRUE);
        KeyboardInput(VK_SCROLL, FALSE);
    }

    if (gameStart.keyboardState.isLeftAltPress && wParam == WM_MBUTTONDOWN) {
        gameStart.CurrentWeapon->ChangeSetting();
    }

    if (gameStart.keyboardState.isLeftAltPress && gameStart.mouseState.isRightButtonPress) {
        gameStart.CurrentWeapon->HoldBreath(true);
        SetMessage();
    }
    else {
        gameStart.CurrentWeapon->HoldBreath(false);
        SetMessage();
    }
    

    if (wParam == WM_RBUTTONDOWN) {
        if (gameStart.keyboardState.canFocus) {
            CreateTimerQueueTimer(&m_timerHandle, NULL, TimerProc, (void*)VK_RSHIFT, 300, 0, WT_EXECUTEINTIMERTHREAD);
        }

    }

    if (wParam == WM_RBUTTONUP) {
        if (gameStart.keyboardState.canFocus) {
            DeleteTimerQueueTimer(NULL, m_timerHandle, NULL);
            KeyboardInput(VK_RSHIFT, FALSE);
        }
    }

    if (wParam == WM_MOUSEWHEEL) {
        if (gameStart.keyboardState.isLeftAltPress) {
            short delta = (short)HIWORD(msllhook->mouseData);
            if (delta > 0) {    //滚轮上
                gameStart.PickPreviousWeapon();
                SetMessage();
            }
            else if (delta < 0) {   //滚轮下
                gameStart.PickNextWeapon();
                SetMessage();
            }
        }

        if (gameStart.keyboardState.isLeftContrlPress) {
            short delta = (short)HIWORD(msllhook->mouseData);
            if (delta > 0) {    //滚轮上
                gameStart.DecrementRecoil();
                SetMessage();
            }
            else if (delta < 0) {   //滚轮下
                gameStart.IncrementRecoil();
                SetMessage();
            }
        }

        
    }


    short key = GetKeyState(VK_SCROLL);
    gameStart.keyboardState.scrollLock = key & 0x0001;


    

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
        if (kbhook->vkCode == VK_LCONTROL) {
            gameStart.keyboardState.isLeftContrlPress = 1;
            gameStart.DoKeyBoardEvent(VK_LCONTROL,1);
        }
        else if (kbhook->vkCode == VK_LSHIFT) {
            gameStart.keyboardState.isLeftShiftPress = 1;
            gameStart.DoKeyBoardEvent(VK_LSHIFT,1); 
        }
        else if (kbhook->vkCode == VK_RSHIFT) {
            gameStart.keyboardState.isRightShiftPress = 1;
        }
        else if (kbhook->vkCode == 0x31) { //1
            gameStart.keyboardState.isNum1Press = 1;
        }
        else if (kbhook->vkCode == 0x32) { //2
            gameStart.keyboardState.isNum2Press = 1;
        }
        else if (kbhook->vkCode == 0x33) { //3
            gameStart.keyboardState.isNum3Press = 1;
        }
        else if (kbhook->vkCode == 0x34) { //4
            gameStart.keyboardState.isNum4Press = 1;
        }
        else if (kbhook->vkCode == 0x35) { //5
            gameStart.keyboardState.isNum5Press = 1;
        }
        else if (kbhook->vkCode == 0x36) { //6
            gameStart.keyboardState.isNum6Press = 1;
        }
        else if (kbhook->vkCode == 0x43) { //C
            gameStart.keyboardState.isC_Press = 1;
            gameStart.DoKeyBoardEvent(0x43, 1);
        }
        else if (kbhook->vkCode == 0x5A) { //Z
            gameStart.keyboardState.isZ_Press = 1;
            gameStart.DoKeyBoardEvent(0x5A, 1);
        }
        else if (kbhook->vkCode == VK_CAPITAL) {
            gameStart.keyboardState.isCapsLockPress = 1;
            gameStart.DoKeyBoardEvent(VK_CAPITAL,1);          
        }
        else if (kbhook->vkCode == VK_TAB) {
            if (gameStart.keyboardState.isTabPress == 0) {
                gameStart.keyboardState.isTabPress = 1;
                CreateTimerQueueTimer(&m_timerHandle2, NULL, TimerProc2, (void*)VK_RSHIFT, 150, 0, WT_EXECUTEINTIMERTHREAD);
            }           
        }
        else if (kbhook->vkCode == VK_NUMPAD2) {
            gameStart.MoveTest(5);
            SetMessage();
        }
        else if (kbhook->vkCode == 0x52) { //R
            gameStart.Reload();
        }
        
    }

    

    if (wParam == WM_KEYUP) {


        if (kbhook->vkCode == VK_LCONTROL) {
            gameStart.keyboardState.isLeftContrlPress = 0;
            gameStart.DoKeyBoardEvent(VK_LCONTROL,0);
        }
        else if (kbhook->vkCode == VK_LSHIFT) {
            gameStart.keyboardState.isLeftShiftPress = 0;
            gameStart.DoKeyBoardEvent(VK_LSHIFT,0);
        }
        else if (kbhook->vkCode == VK_LMENU) {
            gameStart.keyboardState.isLeftAltPress = 0;
        }
        else if (kbhook->vkCode == 0x31) {
            gameStart.keyboardState.isNum1Press = 0;
            gameStart.keyboardState.canFocus = FALSE;
            gameStart.SwitchWeapon(1);
            SetMessage();
        }
        else if (kbhook->vkCode == 0x32) {
            gameStart.keyboardState.isNum2Press = 0;
            gameStart.keyboardState.canFocus = TRUE;
            gameStart.SwitchWeapon(2);
            SetMessage();
        }
        else if (kbhook->vkCode == 0x33) {
            gameStart.keyboardState.isNum3Press = 0;
        }
        else if (kbhook->vkCode == 0x34) {
            gameStart.keyboardState.isNum4Press = 0;
        }
        else if (kbhook->vkCode == 0x35) {
            gameStart.keyboardState.isNum5Press = 0;
        }
        else if (kbhook->vkCode == 0x36) {
            gameStart.keyboardState.isNum6Press = 0;
        }
        else if (kbhook->vkCode == 0x58) { //x
            gameStart.keyboardState.canFocus = FALSE;
        }
        else if (kbhook->vkCode == 0x43) { //C
            gameStart.keyboardState.isC_Press = 0;
            gameStart.DoKeyBoardEvent(0x43, 0);
        }
        else if (kbhook->vkCode == 0x5A) { //Z
            gameStart.keyboardState.isZ_Press = 0;
            gameStart.DoKeyBoardEvent(0x5A, 0);
        }
        else if (kbhook->vkCode == VK_RSHIFT) {
            gameStart.keyboardState.isRightShiftPress = 0;
        }
        else if (kbhook->vkCode == VK_CAPITAL) {
            short key = GetKeyState(VK_CAPITAL);
            gameStart.keyboardState.capsLock = key & 0x0001;  
            gameStart.keyboardState.isCapsLockPress = 0;
            gameStart.DoKeyBoardEvent(VK_CAPITAL,0);     
        }
        else if (kbhook->vkCode == VK_SCROLL) {
            short key = GetKeyState(VK_SCROLL);
            gameStart.keyboardState.scrollLock = key & 0x0001;
        }
        else if (kbhook->vkCode == 0xC0) {  // `~键
            gameStart.PickMatchImageWeapon();
            //MatchProcessThread();
        }
        else if (kbhook->vkCode == VK_TAB) {
            if (gameStart.keyboardState.isTabPress == 1) {
                gameStart.keyboardState.isTabPress = 0;
                //DeleteTimerQueueTimer(NULL, m_timerHandle2, NULL);
            }
        }

        

        if (kbhook->vkCode == VK_NUMPAD1) {
            gameStart.MoveTest(1);
            SetMessage();
        }
        else if (kbhook->vkCode == VK_NUMPAD2) {
            
            SetMessage();
        }
        else if (kbhook->vkCode == VK_NUMPAD3) {
            gameStart.countPx = 0;
            SetMessage();
        }
        else if (kbhook->vkCode == VK_NUMPAD4) {
            
            SetMessage();
        }
        else if (kbhook->vkCode == VK_NUMPAD5) {
            
            SetMessage();
        }
        else if (kbhook->vkCode == VK_NUMPAD6) {
            
            SetMessage();
        }
        else if (kbhook->vkCode == VK_NUMPAD7) {
            
            SetMessage();
        }
        else if (kbhook->vkCode == VK_NUMPAD8) {
            
            SetMessage();
        }
        else if (kbhook->vkCode == VK_NUMPAD9) {
            
            SetMessage();
        }
        else if (kbhook->vkCode == VK_DIVIDE) {
            
            SetMessage();
        }
        else if (kbhook->vkCode == VK_MULTIPLY) {
            
            SetMessage();
        }
        else if (kbhook->vkCode == VK_SUBTRACT) {
            
            SetMessage();
        }
        else if (kbhook->vkCode == VK_ADD) {
            
            SetMessage();
        }
        else if (kbhook->vkCode == VK_NUMPAD0) {
            gameStart.CurrentWeapon->ResetWeapon();
            gameStart.PickWeapon("Default");            
        }
        else if (kbhook->vkCode == VK_UP) {
            gameStart.PickPreviousWeapon();
        }
        else if (kbhook->vkCode == VK_DOWN) {
            gameStart.PickNextWeapon();
        }
        else if (kbhook->vkCode == VK_LEFT) {
            gameStart.DecrementRecoil();
        }
        else if (kbhook->vkCode == VK_RIGHT) {
            gameStart.IncrementRecoil();
        }

    }

    if (wParam == WM_SYSKEYDOWN) {
        if (kbhook->vkCode == VK_LMENU) {
            gameStart.keyboardState.isLeftAltPress = 1;
            gameStart.DoKeyBoardEvent(VK_LMENU,1);
        }
        else if (kbhook->vkCode == 0x31) {
            gameStart.keyboardState.isNum1Press = 1;
        }
        else if (kbhook->vkCode == 0x32) {
            gameStart.keyboardState.isNum2Press = 1;
        }
        else if (kbhook->vkCode == 0x33) {
            gameStart.keyboardState.isNum3Press = 1;
        }
        else if (kbhook->vkCode == 0x34) {
            gameStart.keyboardState.isNum4Press = 1;
        }
        else if (kbhook->vkCode == 0x35) {
            gameStart.keyboardState.isNum5Press = 1;
        }
        else if (kbhook->vkCode == 0x36) {
            gameStart.keyboardState.isNum6Press = 1;
        }
        else if (kbhook->vkCode == 0x54) {
            gameStart.keyboardState.isT_Press = 1;
        }
        else if (kbhook->vkCode == VK_XBUTTON1) {
            
        }
        else if (kbhook->vkCode == VK_XBUTTON2) {
            
        }
    }

    if (wParam == WM_SYSKEYUP) {
         if (kbhook->vkCode == VK_LMENU) {
             gameStart.keyboardState.isLeftAltPress = 0;
            gameStart.DoKeyBoardEvent(VK_LMENU,0);
         }
         else if (kbhook->vkCode == 0x31) {
             gameStart.keyboardState.isNum1Press = 0;
         }
         else if (kbhook->vkCode == 0x32) {
             gameStart.keyboardState.isNum2Press = 0;
         }
         else if (kbhook->vkCode == 0x33) {
             gameStart.keyboardState.isNum3Press = 0;
         }
         else if (kbhook->vkCode == 0x34) {
             gameStart.keyboardState.isNum4Press = 0;
         }
         else if (kbhook->vkCode == 0x35) {
             gameStart.keyboardState.isNum5Press = 0;
         }
         else if (kbhook->vkCode == 0x36) {
             gameStart.keyboardState.isNum6Press = 0;
         }
         else if (kbhook->vkCode == 0x54) {
             gameStart.keyboardState.isT_Press = 0;
         }
    }

    //////////////////////////
    if (gameStart.keyboardState.isLeftAltPress && gameStart.keyboardState.isNum1Press) {
        gameStart.AssembleScope(1);
        SetMessage();
    }
    if (gameStart.keyboardState.isLeftAltPress && gameStart.keyboardState.isNum2Press) {
        gameStart.AssembleScope(2);
        SetMessage();
    }
    if (gameStart.keyboardState.isLeftAltPress && gameStart.keyboardState.isNum3Press) {
        gameStart.AssembleScope(3);
        SetMessage();
    }
    if (gameStart.keyboardState.isLeftAltPress && gameStart.keyboardState.isNum4Press) {
        gameStart.AssembleScope(4);
        SetMessage();
    }
    if (gameStart.keyboardState.isLeftAltPress && gameStart.keyboardState.isNum5Press) {
        gameStart.AssembleScope(6);
        SetMessage();
    }
    if (gameStart.keyboardState.isLeftAltPress && gameStart.keyboardState.isNum6Press) {
        gameStart.AssembleScope(8);
        SetMessage();
    }
    if (gameStart.keyboardState.isLeftAltPress && gameStart.keyboardState.isT_Press) {
        
    }

    return 0;
}



HANDLE StartProcessThread() {
    m_hThread = (HANDLE)_beginthreadex(NULL, 0, &ThreadProc, NULL, 0, &m_ThreadId);
    return HANDLE();
}

HANDLE MatchProcessThread()
{
    m_hMatchThread = (HANDLE)_beginthreadex(NULL, 0, &MatchThreadProc, NULL, 0, &m_ThreadId);
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

unsigned __stdcall MatchThreadProc(void* o) {
    gameStart.PickMatchImageWeapon();
    _endthreadex(0);
    return 0;
}

void KeyboardInput(UINT key, BOOL isKeyDown) {
    UINT scanCode = MapVirtualKey(key, MAPVK_VK_TO_VSC_EX);
    if (isKeyDown) {
        keybd_event(key, scanCode, 0, 0);
    }
    else {
        keybd_event(key, scanCode, KEYEVENTF_KEYUP, 0);

    }
}

void CALLBACK TimerProc(void* key, BOOLEAN TimerOrWaitFired) {
    KeyboardInput(VK_RSHIFT, TRUE);
}

void CALLBACK TimerProc2(void* key, BOOLEAN TimerOrWaitFired) {
    if (gameStart.allowMatch) {
        gameStart.allowMatch = false;
        CreateTimerQueueTimer(&m_timerHandle3, NULL, TimerProc3, NULL, 3000, 0, WT_EXECUTEINTIMERTHREAD);
        gameStart.PickMatchImageWeapon();
    }
    
}

void CALLBACK TimerProc3(void* key, BOOLEAN TimerOrWaitFired) {
    gameStart.allowMatch = true;
}



void SetMessage() {
    char lmessage[1024];
    sprintf_s(lmessage, 1024, "%s", gameStart.CurrentWeapon->weaponName.c_str());
    //SetWindowTextA(hStaticText, lmessage);
    SetWindowTextA(hMessageText, lmessage);
    sprintf_s(lmessage, 1024, "%d",  gameStart.CurrentWeapon->scope->scope);
    //SetWindowTextA(hStaticText2, lmessage);
    SetWindowTextA(hMessageText2, lmessage);
    sprintf_s(lmessage, 1024, "%.2f", gameStart.CurrentWeapon->recoilBaseRunning);
    //SetWindowTextA(hStaticText3, lmessage);
    SetWindowTextA(hMessageText3, lmessage);
    //sprintf_s(lmessage, 1024, "%s", gameStart.CurrentWeapon->muzzle != NULL ? gameStart.CurrentWeapon->muzzle->name.c_str() : "");
    sprintf_s(lmessage, 1024, "%d", gameStart.countPx);
    SetWindowTextA(hMessageText4, lmessage);
    //sprintf_s(lmessage, 1024, "%s", gameStart.CurrentWeapon->grip != NULL ? gameStart.CurrentWeapon->grip->name.c_str() : "");
    sprintf_s(lmessage, 1024, "%d", gameStart.CurrentWeapon->currentShot);
    SetWindowTextA(hMessageText5, lmessage);
    //sprintf_s(lmessage, 1024, "%s", gameStart.CurrentWeapon->stock != NULL ? gameStart.CurrentWeapon->stock->name.c_str() : "");
    sprintf_s(lmessage, 1024, "%.2f", gameStart.CurrentWeapon->attachmentEffect);
    SetWindowTextA(hMessageText6, lmessage);
}
