//#pragma once
//#include <Windows.h>
//#include <opencv2/opencv.hpp>
//#include <opencv2/highgui.hpp>
//using cv::Mat;
//class Screenshot
//{
//public:
//    Screenshot()
//    {
//        double zoom = getZoom();
//        m_width = GetSystemMetrics(SM_CXSCREEN) * zoom;
//        m_height = GetSystemMetrics(SM_CYSCREEN) * zoom;
//        m_screenshotData = new char[m_width * m_height * 4];
//        memset(m_screenshotData, 0, m_width);
//
//        // 获取屏幕 DC
//        m_screenDC = GetDC(NULL);
//        m_compatibleDC = CreateCompatibleDC(m_screenDC);
//
//        // 创建位图
//        m_hBitmap = CreateCompatibleBitmap(m_screenDC, m_width, m_height);
//        SelectObject(m_compatibleDC, m_hBitmap);
//    }
//    double static getZoom()
//    {
//        // 获取窗口当前显示的监视器
//        HWND hWnd = GetDesktopWindow();
//        HMONITOR hMonitor = MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST);
//
//        // 获取监视器逻辑宽度
//        MONITORINFOEX monitorInfo;
//        monitorInfo.cbSize = sizeof(monitorInfo);
//        GetMonitorInfo(hMonitor, &monitorInfo);
//        int cxLogical = (monitorInfo.rcMonitor.right - monitorInfo.rcMonitor.left);
//
//        // 获取监视器物理宽度
//        DEVMODE dm;
//        dm.dmSize = sizeof(dm);
//        dm.dmDriverExtra = 0;
//        EnumDisplaySettings(monitorInfo.szDevice, ENUM_CURRENT_SETTINGS, &dm);
//        int cxPhysical = dm.dmPelsWidth;
//
//        return cxPhysical * 1.0 / cxLogical;
//    }
//
//    cv::Mat getScreenshot()
//    {
//        // 得到位图的数据
//        BitBlt(m_compatibleDC, 0, 0, m_width, m_height, m_screenDC, 0, 0, SRCCOPY);
//        GetBitmapBits(m_hBitmap, m_width * m_height * 4, m_screenshotData);
//
//        // 创建图像
//        Mat screenshot(m_height, m_width, CV_8UC4, m_screenshotData);
//        //cv::imwrite("starry_night.png", screenshot);
//        return screenshot;
//    }
//
//    cv::Mat getScreenshot(int x, int y, int width, int height)
//    {
//        Mat screenshot = getScreenshot();
//        return screenshot(cv::Rect(x, y, width, height));
//    }
//
//private:
//    int m_width;
//    int m_height;
//    HDC m_screenDC;
//    HDC m_compatibleDC;
//    HBITMAP m_hBitmap;
//    LPVOID m_screenshotData = nullptr;
//};