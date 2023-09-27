﻿// NoRecoil.cpp : 定义应用程序的入口点。
//

#include "framework.h"
#include "NoRecoil.h"
#include <Unknwn.h>
#include <gdiplus.h>
#pragma comment(lib,"Gdiplus.lib")
#include "GameStart.h"

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
DWORD StaticTextStyle = SS_CENTER | SS_LEFT | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE;
//键盘钩子
HHOOK keyboardHook;
//鼠标钩子
HHOOK mouseHook;
//句柄
HWND hStaticText;
HWND hButton;
HWND hButton2;
HWND hInput0;
HWND hInput1;
HWND hList1;
HANDLE m_hThread;
UINT m_ThreadId;
LONG volatile m_IsShouldThreadFinish{ FALSE };
LONG volatile startFalg{ TRUE };
unsigned __stdcall ThreadProc(void* mouseState);


#define IDB_ONE     3301
#define IDB_TWO     3302
#define IDB_LIST1     3303

//鼠标状态
struct Mouse_State {
    int isRightButtonPress = 0;
    int isLeftButtonPress = 0;
    int continuousTap = FALSE;
    int isStartContinuousTap = FALSE;
    int count = 0;
};
Mouse_State mouseState;

//键盘状态
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
    int scrollLock = 0;
    int canFocus = FALSE;
};
KeyBoard_State keyboardState;


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
void DrawMessageWindows(HWND hkeyboardWnd, std::string msg);

HANDLE m_timerHandle = NULL;
HANDLE m_timerHandle2 = NULL;
void KeyboardInput(UINT key, BOOL isKeyDown);
void CALLBACK TimerProc(void* key, BOOLEAN TimerOrWaitFired);
void CALLBACK TimerProc2(void* key, BOOLEAN TimerOrWaitFired);

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
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_NORECOIL);
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
    wcex.hbrBackground = (HBRUSH)CreateSolidBrush(0x000000);//(HBRUSH)(COLOR_WINDOW + 1);
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
        CW_USEDEFAULT, 0, 600, 300, nullptr, nullptr, hInstance, nullptr);

    hMessageWnd = CreateWindowW(L"Message", L"", WS_OVERLAPPEDWINDOW,//WS_POPUP,WS_BORDER | WS_SIZEBOX
        10, 10, 200, 200, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);


    //窗口置顶
    //SetWindowPos(hMessageWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
    //ShowWindow(hMessageWnd, SW_SHOWNA);
    //DrawMessageWindows(hMessageWnd, "");
    

    //SetWindowLong(hMessageWnd, GWL_EXSTYLE, GetWindowLong(hMessageWnd, GWL_EXSTYLE) | WS_EX_LAYERED | WS_EX_TRANSPARENT);
    //UpdateWindow(hMessageWnd);

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
        hStaticText = CreateWindow(L"Static", L"", StaticTextStyle, 220, 10, 200, 50, hWnd, NULL, hInst, NULL);
        hButton = CreateWindow(L"Button", L"X", StaticTextStyle, 10, 10, 100, 40, hWnd, (HMENU)IDB_ONE, hInst, NULL);
        hList1 = CreateWindow(L"LISTBOX", L"T", StaticTextStyle | WS_VSCROLL, 10, 60, 100, 100, hWnd, (HMENU)IDB_LIST1, hInst, NULL);
        hInput0 = CreateWindowA("EDIT", "1", StaticTextStyle, 150, 80, 30, 30, hWnd, (HMENU)IDB_ONE, hInst, NULL);
        hInput1 = CreateWindowA("EDIT", "1", StaticTextStyle, 150, 115, 30, 30, hWnd, (HMENU)IDB_ONE, hInst, NULL);

        hButton2 = CreateWindow(L"Button", L"Ok", StaticTextStyle, 200, 150, 30, 30, hWnd, (HMENU)IDB_TWO, hInst, NULL);

        for (auto& t : gameStart.lib.weaponMap) {
            SendMessageA(hList1, LB_ADDSTRING, 0, (LPARAM)t.first.c_str());
        }
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
                if (startFalg == FALSE)
                    startFalg = TRUE;
                else
                    startFalg = FALSE;


            }
            }
            break;
        case IDB_TWO: 
            switch (HIWORD(wParam)) {
            case BN_CLICKED:
            {

                int nSel = SendMessage(hList1, LB_GETCURSEL, 0, 0);
                char tem[128] = { 0 };
                SendMessageA(hList1, LB_GETTEXT, nSel, (LPARAM)tem);
                std::string weaponName = std::string(tem);

                wchar_t buff[1024];
                Edit_GetText(hInput0, buff, 1024);
                gameStart.lib.FindWeapon(weaponName)->noAttachmentRecoil = _tstoi(buff);
                Edit_GetText(hInput1, buff, 1024);
                gameStart.lib.FindWeapon(weaponName)->fullAttachmentRecoil = _tstoi(buff);

                gameStart.lib.FindWeapon(weaponName)->ChangeSetting();
            }
            }

        case IDB_LIST1:
            switch (HIWORD(wParam)) {
            case LBN_DBLCLK:
            {           
                int nSel = SendMessage(hList1, LB_GETCURSEL, 0, 0);
                char tem[128] = { 0 };
                SendMessageA(hList1, LB_GETTEXT, nSel, (LPARAM)tem);
                std::string weaponName = std::string(tem);

                Edit_SetText(hInput0, std::to_wstring(gameStart.lib.FindWeapon(weaponName)->noAttachmentRecoil).c_str());
                Edit_SetText(hInput1, std::to_wstring(gameStart.lib.FindWeapon(weaponName)->fullAttachmentRecoil).c_str());
            }
            }
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
LRESULT CALLBACK WndProc2(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
    {
        
    }
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        int a = 0;
        // 分析菜单选择:
        switch (wmId)
        {           
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
        //DrawMessageWindows(hWnd, "");
        FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
        //DrawText(hdc, L"123456", 7, &ps.rcPaint, 0);
        RECT wndRect;
        ::GetWindowRect(hWnd, &wndRect);
        SIZE wndSize = { wndRect.right - wndRect.left,wndRect.bottom - wndRect.top };
        //HDC memDC = ::CreateCompatibleDC(hdc);
        //HDC screenDC = GetDC(NULL);
        //POINT ptSrc = { 0,0 };

        //BLENDFUNCTION blendFunction;
        //blendFunction.AlphaFormat = AC_SRC_ALPHA;
        //blendFunction.BlendFlags = 0;
        //blendFunction.BlendOp = AC_SRC_OVER;
        //blendFunction.SourceConstantAlpha = 255;
        //UpdateLayeredWindow(hWnd, screenDC, /*&ptSrc*/NULL, &wndSize, memDC, &ptSrc, 0, &blendFunction, ULW_ALPHA);
        //::DeleteDC(memDC);
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
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
    keyboardState.capsLock = key & 0x0001;

    key = GetKeyState(VK_SCROLL);
    keyboardState.scrollLock = key & 0x0001;

    gameStart.LoadSetting();


    //设置鼠标钩子
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
        mouseState.isLeftButtonPress = 1;
        break;
    case WM_LBUTTONUP:
        mouseState.isLeftButtonPress = 0;
        break;
    case WM_RBUTTONDOWN:
        mouseState.isRightButtonPress = 1;
        break;
    case WM_RBUTTONUP:
        mouseState.isRightButtonPress = 0;
        break;
    }

    if (keyboardState.isLeftAltPress && wParam == WM_RBUTTONUP && !mouseState.isLeftButtonPress) {
        KeyboardInput(VK_SCROLL, TRUE);
        KeyboardInput(VK_SCROLL, FALSE);
    }

    if (wParam == WM_RBUTTONDOWN) {
        if (keyboardState.canFocus) {
            CreateTimerQueueTimer(&m_timerHandle, NULL, TimerProc, (void*)VK_RSHIFT, 300, 0, WT_EXECUTEINTIMERTHREAD);
        }

    }

    if (wParam == WM_RBUTTONUP) {
        if (keyboardState.canFocus) {
            DeleteTimerQueueTimer(NULL, m_timerHandle, NULL);
            KeyboardInput(VK_RSHIFT, FALSE);
        }
    }


    short key = GetKeyState(VK_SCROLL);
    keyboardState.scrollLock = key & 0x0001;


    char lmessage[1024];
    sprintf_s(lmessage, 1024, "weaponName : %s \nscope : %d", gameStart.CurrentWeapon->weaponName.c_str(), gameStart.CurrentWeapon->scope);
    SetWindowTextA(hStaticText, lmessage);

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
            keyboardState.isLeftContrlPress = 1;
        }
        else if (kbhook->vkCode == VK_LSHIFT) {
            keyboardState.isLeftShiftPress = 1;
        }
        else if (kbhook->vkCode == VK_RSHIFT) {
            keyboardState.isRightShiftPress = 1;
        }
        else if (kbhook->vkCode == 0x31) { //1
            keyboardState.isNum1Press = 1;
        }
        else if (kbhook->vkCode == 0x32) { //2
            keyboardState.isNum2Press = 1;
        }
        else if (kbhook->vkCode == 0x33) { //2
            keyboardState.isNum3Press = 1;
        }
        else if (kbhook->vkCode == 0x34) { //2
            keyboardState.isNum4Press = 1;
        }
        //else if (kbhook->vkCode == 0x52) { //R
        //    function.Reload();
        //}
        
    }

    if (wParam == WM_SYSKEYDOWN) {
        if (kbhook->vkCode == VK_LMENU) {
            keyboardState.isLeftAltPress = 1;
        }
        else if (kbhook->vkCode == 0x31) {
            keyboardState.isNum1Press = 1;
        }
        else if (kbhook->vkCode == 0x32) {
            keyboardState.isNum2Press = 1;
        }
        else if (kbhook->vkCode == 0x33) {
            keyboardState.isNum3Press = 1;
        }
        else if (kbhook->vkCode == 0x34) {
            keyboardState.isNum4Press = 1;
        }
    }

    if (wParam == WM_KEYUP) {


        if (kbhook->vkCode == VK_LCONTROL) {
            keyboardState.isLeftContrlPress = 0;
        }
        else if (kbhook->vkCode == VK_LSHIFT) {
            keyboardState.isLeftShiftPress = 0;
        }
        else if (kbhook->vkCode == VK_LMENU) {
            keyboardState.isLeftAltPress = 0;
        }
        else if (kbhook->vkCode == 0x31) {
            keyboardState.isNum1Press = 0;
            keyboardState.canFocus = FALSE;
        }
        else if (kbhook->vkCode == 0x32) {
            keyboardState.isNum2Press = 0;
            keyboardState.canFocus = TRUE;
        }
        else if (kbhook->vkCode == 0x33) {
            keyboardState.isNum3Press = 0;
        }
        else if (kbhook->vkCode == 0x34) {
            keyboardState.isNum4Press = 0;
        }
        else if (kbhook->vkCode == 0x58) {
            keyboardState.canFocus = FALSE;
        }
        else if (kbhook->vkCode == VK_RSHIFT) {
            keyboardState.isRightShiftPress = 0;
        }
        else if (kbhook->vkCode == VK_CAPITAL) {
            short key = GetKeyState(VK_CAPITAL);
            keyboardState.capsLock = key & 0x0001;
        }
        else if (kbhook->vkCode == VK_SCROLL) {
            short key = GetKeyState(VK_SCROLL);
            keyboardState.scrollLock = key & 0x0001;
        }

        if (kbhook->vkCode == VK_NUMPAD1) {
            gameStart.SwitchWeapon("UMP45");
        }
        else if (kbhook->vkCode == VK_NUMPAD2) {
            gameStart.SwitchWeapon("Tommy Gun");
        }
        else if (kbhook->vkCode == VK_NUMPAD3) {
            gameStart.SwitchWeapon("Vector");
        }
        else if (kbhook->vkCode == VK_NUMPAD4) {
            gameStart.SwitchWeapon("SCAR-L");
        }
        else if (kbhook->vkCode == VK_NUMPAD5) {
            gameStart.SwitchWeapon("M416");
        }
        else if (kbhook->vkCode == VK_NUMPAD6) {
            gameStart.SwitchWeapon("M16A4");
        }
        else if (kbhook->vkCode == VK_NUMPAD7) {
            gameStart.SwitchWeapon("ACE32");
        }
        else if (kbhook->vkCode == VK_NUMPAD8) {
            gameStart.SwitchWeapon("Beryl M762");
        }
        else if (kbhook->vkCode == VK_NUMPAD9) {
            gameStart.SwitchWeapon("Mk47 Mutant");
        }
        else if (kbhook->vkCode == VK_NUMPAD0) {
            gameStart.SwitchWeapon("VSS");
        }

    }

    if (wParam == WM_SYSKEYUP) {
         if (kbhook->vkCode == VK_LMENU) {
            keyboardState.isLeftAltPress = 0;
         }
         else if (kbhook->vkCode == 0x31) {
             keyboardState.isNum1Press = 0;
         }
         else if (kbhook->vkCode == 0x32) {
             keyboardState.isNum2Press = 0;
         }
         else if (kbhook->vkCode == 0x33) {
             keyboardState.isNum3Press = 0;
         }
         else if (kbhook->vkCode == 0x34) {
             keyboardState.isNum4Press = 0;
         }
    }

    //////////////////////////
    if (keyboardState.isLeftAltPress && keyboardState.isNum1Press) {
        gameStart.CurrentWeapon->AssembleScope(0);
    }
    if (keyboardState.isLeftAltPress && keyboardState.isNum2Press) {
        gameStart.CurrentWeapon->AssembleScope(2);
    }
    if (keyboardState.isLeftAltPress && keyboardState.isNum3Press) {
        gameStart.CurrentWeapon->AssembleScope(3);
    }
    if (keyboardState.isLeftAltPress && keyboardState.isNum4Press) {
        gameStart.CurrentWeapon->AssembleScope(4);
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
            gameStart.Move(keyboardState.capsLock, keyboardState.scrollLock, mouseState.isRightButtonPress && mouseState.isLeftButtonPress, keyboardState.isLeftContrlPress && mouseState.isLeftButtonPress);
        }
    }
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
    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
    Sleep(gameStart.CurrentWeapon->interval);
    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
    mouseState.count++;
}

void DrawMessageWindows(HWND hkeyboardWnd,std::string msg) {
    RECT wndRect;
    ::GetWindowRect(hkeyboardWnd, &wndRect);
    SIZE wndSize = { wndRect.right - wndRect.left,wndRect.bottom - wndRect.top };
    HDC hdc = ::GetDC(hkeyboardWnd);
    HDC memDC = ::CreateCompatibleDC(hdc);
    HBITMAP memBitmap = ::CreateCompatibleBitmap(hdc, wndSize.cx, wndSize.cy);
    ::SelectObject(memDC, memBitmap);


    Gdiplus::Graphics graphics(memDC);

    Gdiplus::SolidBrush  brush(Gdiplus::Color(0,0, 0, 0));
    Gdiplus::FontFamily  fontFamily(L"Times New Roman");
    Gdiplus::Font font(&fontFamily, 24, Gdiplus::FontStyleRegular, Gdiplus::UnitPixel);


    RECT rc;
    GetClientRect(hkeyboardWnd, &rc);
    INT left = rc.left;
    INT top = rc.top;
    INT right = rc.right;
    INT bottom = rc.bottom;

    Gdiplus::PointF RegionPoint = Gdiplus::PointF(left, top);

    graphics.DrawString(L"123", 3, &font, RegionPoint, &brush);
    Gdiplus::Rect gdiRect{ rc.left ,rc.top ,rc.right - rc.left ,rc.bottom - rc.top };
    graphics.FillRectangle(&brush, gdiRect);

    // get screen dc 
    HDC screenDC = GetDC(NULL);
    POINT ptSrc = { 0,0 };

    //BLENDFUNCTION blendFunction;
    //blendFunction.AlphaFormat = AC_SRC_ALPHA;
    //blendFunction.BlendFlags = 0;
    //blendFunction.BlendOp = AC_SRC_OVER;
    //blendFunction.SourceConstantAlpha = 255;
    //UpdateLayeredWindow(hkeyboardWnd, screenDC, /*&ptSrc*/NULL, &wndSize, memDC, &ptSrc, 0, &blendFunction, ULW_ALPHA);

    ::DeleteDC(memDC);
    ::DeleteObject(memBitmap);

}
