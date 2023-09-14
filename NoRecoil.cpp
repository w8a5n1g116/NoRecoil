// NoRecoil.cpp : 定义应用程序的入口点。
//

#include "framework.h"
#include "NoRecoil.h"

#define MAX_LOADSTRING 100

// 全局变量:
HINSTANCE hInst;                                // 当前实例
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名
HWND hWnd;

// 此代码模块中包含的函数的前向声明:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
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
HWND hInput0;
HWND hInput1;
HWND hInput2;
HWND hInput3;
HWND hInput4;
HWND hInput5;
HWND hInput6;
HWND hInput7;
HANDLE m_hThread;
UINT m_ThreadId;
LONG volatile m_IsShouldThreadFinish{ FALSE };
LONG volatile startFalg{ TRUE };
unsigned __stdcall ThreadProc(void* mouseState);


#define IDB_ONE     3301

//鼠标状态
struct Mouse_State {
    int isRightButtonPress = 0;
    int isLeftButtonPress = 0;
    int count = 0;
};
Mouse_State mouseState;

//键盘状态
struct KeyBoard_State {
    int isLeftContrlPress = 0;
    int isLeftShiftPress = 0;
    int isNum1Press = 0;
    int isNum2Press = 0;
};
KeyBoard_State keyboardState;

struct Config {
    int interval = 10;
    int offset = 1;
    int offset_1 = 1;
    int offset_2 = 1;
    int offset_3 = 1;
    int offset_4 = 1;
    int offset_6 = 1;
    int offset_8 = 1;
    int profile = 0;
};
Config config;

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
void Process(WPARAM wParam, MSLLHOOKSTRUCT* msllhook);
HANDLE StartProcessThread();



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

    // 执行应用程序初始化:
    if (!InitInstance (hInstance, nCmdShow))
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

    return (int) msg.wParam;
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

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_NORECOIL));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_NORECOIL);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

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
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

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
            //hStaticText =   CreateWindow(L"Static", L"", StaticTextStyle, 10, 10, 400, 50, hWnd, NULL, hInst, NULL);
            hButton =       CreateWindow(L"Button", L"X", StaticTextStyle, 10, 100, 100, 100, hWnd, (HMENU)IDB_ONE, hInst, NULL);
            hInput0 =       CreateWindow(L"EDIT", std::to_wstring(config.interval).c_str(), StaticTextStyle, 120, 100, 30, 30, hWnd, (HMENU)IDB_ONE, hInst, NULL);
            hInput1 =       CreateWindow(L"EDIT", std::to_wstring(config.offset).c_str(), StaticTextStyle, 170, 100, 30, 30, hWnd, (HMENU)IDB_ONE, hInst, NULL);
            hInput2 =       CreateWindow(L"EDIT", std::to_wstring(config.offset_1).c_str(), StaticTextStyle, 220, 100, 30, 30, hWnd, (HMENU)IDB_ONE, hInst, NULL);
            hInput3 =       CreateWindow(L"EDIT", std::to_wstring(config.offset_2).c_str(), StaticTextStyle, 270, 100, 30, 30, hWnd, (HMENU)IDB_ONE, hInst, NULL);
            hInput4 =       CreateWindow(L"EDIT", std::to_wstring(config.offset_3).c_str(), StaticTextStyle, 320, 100, 30, 30, hWnd, (HMENU)IDB_ONE, hInst, NULL);
            hInput5 =       CreateWindow(L"EDIT", std::to_wstring(config.offset_4).c_str(), StaticTextStyle, 370, 100, 30, 30, hWnd, (HMENU)IDB_ONE, hInst, NULL);
            hInput6 =       CreateWindow(L"EDIT", std::to_wstring(config.offset_6).c_str(), StaticTextStyle, 420, 100, 30, 30, hWnd, (HMENU)IDB_ONE, hInst, NULL);
            hInput7 =       CreateWindow(L"EDIT", std::to_wstring(config.offset_8).c_str(), StaticTextStyle, 470, 100, 30, 30, hWnd, (HMENU)IDB_ONE, hInst, NULL);
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

                        wchar_t buff[1024];
                        Edit_GetText(hInput0, buff, 1024);
                        WritePrivateProfileString(L"General", L"interval", buff, iniFilePath.c_str());
                        Edit_GetText(hInput1, buff, 1024);
                        WritePrivateProfileString(L"General", L"offset", buff, iniFilePath.c_str());
                        config.offset = _tstoi(buff);
                        Edit_GetText(hInput2, buff, 1024);
                        WritePrivateProfileString(L"General", L"offset_1", buff, iniFilePath.c_str());
                        config.offset_1 = _tstoi(buff);
                        Edit_GetText(hInput3, buff, 1024);
                        WritePrivateProfileString(L"General", L"offset_2", buff, iniFilePath.c_str());
                        config.offset_2 = _tstoi(buff);
                        Edit_GetText(hInput4, buff, 1024);
                        WritePrivateProfileString(L"General", L"offset_3", buff, iniFilePath.c_str());
                        config.offset_3 = _tstoi(buff);
                        Edit_GetText(hInput5, buff, 1024);
                        WritePrivateProfileString(L"General", L"offset_4", buff, iniFilePath.c_str());
                        config.offset_4 = _tstoi(buff);
                        Edit_GetText(hInput6, buff, 1024);
                        WritePrivateProfileString(L"General", L"offset_6", buff, iniFilePath.c_str());
                        config.offset_6 = _tstoi(buff);
                        Edit_GetText(hInput7, buff, 1024);
                        WritePrivateProfileString(L"General", L"offset_8", buff, iniFilePath.c_str());
                        config.offset_8 = _tstoi(buff);

                        
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
    config.interval = GetPrivateProfileInt(L"General", L"interval", 5, iniFilePath.c_str());
    config.offset = GetPrivateProfileInt(L"General", L"offset", 2, iniFilePath.c_str());
    config.offset_1 = GetPrivateProfileInt(L"General", L"offset_1", 2, iniFilePath.c_str());
    config.offset_2 = GetPrivateProfileInt(L"General", L"offset_2", 10, iniFilePath.c_str());
    config.offset_3 = GetPrivateProfileInt(L"General", L"offset_3", 10, iniFilePath.c_str());
    config.offset_4 = GetPrivateProfileInt(L"General", L"offset_4", 10, iniFilePath.c_str());
    config.offset_6 = GetPrivateProfileInt(L"General", L"offset_6", 10, iniFilePath.c_str());
    config.offset_8 = GetPrivateProfileInt(L"General", L"offset_8", 10, iniFilePath.c_str());
    Edit_SetText(hInput0, std::to_wstring(config.interval).c_str());
    Edit_SetText(hInput1, std::to_wstring(config.offset).c_str());
    Edit_SetText(hInput2, std::to_wstring(config.offset_1).c_str());
    Edit_SetText(hInput3, std::to_wstring(config.offset_2).c_str());
    Edit_SetText(hInput4, std::to_wstring(config.offset_3).c_str());
    Edit_SetText(hInput5, std::to_wstring(config.offset_4).c_str());
    Edit_SetText(hInput6, std::to_wstring(config.offset_6).c_str());
    Edit_SetText(hInput7, std::to_wstring(config.offset_8).c_str());
    //设置鼠标钩子
    mouseHook = SetWindowsHookEx(WH_MOUSE_LL, LowLevelMouseProc, GetModuleHandle(NULL),0);
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
    Process(wParam, msllhook);
    //wchar_t lmessage[1024];
    //swprintf_s(lmessage, 1024, L"Code:%d,WPARAM:%d,Point:%d,%d,LLMHF_INJECTED:%d \n isRight:%d,isLeft:%d \n Count:%d", nCode, wParam, msllhook->pt.x, msllhook->pt.y,msllhook->flags, mouseState.isRightButtonPress, mouseState.isLeftButtonPress, mouseState.count);
    //SetWindowText(hStaticText, lmessage);

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
        else if (kbhook->vkCode == 0x31) {
            keyboardState.isNum1Press = 1;
        }
        else if (kbhook->vkCode == 0x32) {
            keyboardState.isNum2Press = 1;
        }
    }
    if (wParam == WM_KEYUP) {
        
         
        if (kbhook->vkCode == VK_LCONTROL) {
            keyboardState.isLeftContrlPress = 0;
        }
        else if (kbhook->vkCode == VK_LSHIFT) {
            keyboardState.isLeftShiftPress = 0;
        }
        else if (kbhook->vkCode == 0x31) {
            keyboardState.isNum1Press = 0;
        }
        else if (kbhook->vkCode == 0x32) {
            keyboardState.isNum2Press = 0;
        }

        if (kbhook->vkCode == VK_NUMPAD0) {
            config.profile = 0;
        }
        else if (kbhook->vkCode == VK_NUMPAD1) {
            config.profile = 1;
        }
        else if (kbhook->vkCode == VK_NUMPAD2) {
            config.profile = 2;
        }
        else if (kbhook->vkCode == VK_NUMPAD3) {
            config.profile = 3;
        }
        else if (kbhook->vkCode == VK_NUMPAD4) {
            config.profile = 4;
        }
        else if (kbhook->vkCode == VK_NUMPAD6) {
            config.profile = 6;
        }
        else if (kbhook->vkCode == VK_NUMPAD8) {
            config.profile = 8;
        }
        
    }

    return 0;
}

void Process(WPARAM wParam, MSLLHOOKSTRUCT* msllhook)
{
    //msllhook->flags != 1 &&
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

    if (mouseState.isRightButtonPress && mouseState.isLeftButtonPress) {
        
        
    }
    
}

HANDLE StartProcessThread() {
    m_hThread = (HANDLE)_beginthreadex(NULL, 0, &ThreadProc, NULL, 0, &m_ThreadId);
    return HANDLE();
}

unsigned __stdcall ThreadProc(void* o) {
    //Mouse_State* state = (Mouse_State*)mouseState;
    while (m_IsShouldThreadFinish == FALSE) {
        if (startFalg == TRUE) {
            if (mouseState.isRightButtonPress && mouseState.isLeftButtonPress) {
                mouseState.count++;

                /*SYSTEMTIME time;
                GetSystemTime(&time);
                double timespan = (((3600 * time.wHour) + (60 * time.wMinute) + time.wSecond) * 1000 + time.wMilliseconds);
                double x = config.x_amplitude * sin(config.x_period * timespan);*/
                int y = 0;
                switch (config.profile)
                {
                case 0:
                    y = config.offset;
                    break;
                case 1:
                    y = config.offset_1;
                    break;
                case 2:
                    y = config.offset_2;
                    break;
                case 3:
                    y = config.offset_3;
                    break;
                case 4:
                    y = config.offset_4;
                    break;
                case 6:
                    y = config.offset_6;
                    break;
                case 8:
                    y = config.offset_8;
                    break;
                default:
                    break;
                }
                mouse_event(MOUSEEVENTF_MOVE, 0, y, 0, 0);
            }
            else if (keyboardState.isLeftContrlPress && mouseState.isLeftButtonPress) {
                int y = config.offset;
                mouse_event(MOUSEEVENTF_MOVE, 0, y, 0, 0);
            }
        } 
        Sleep(config.interval);
    }  
    _endthreadex(0);
    return 0;
}

