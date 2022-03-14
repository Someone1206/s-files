#include <Windows.h>
#include <iostream>
#include "core\consoleUtils.h"
#include "core\prefs.h"
#include "mainWindowProc.h"
#include "err\err.h"
#include "core\TitMgr.h"
#include "MainWindow.h"
#include "GUI_fns.h"

MainWindowOrganised MainWindow;

int CALLBACK WinMain(
        HINSTANCE hInst,
        HINSTANCE hpi,
        LPSTR     args,
        int       idk
        )
{
    InitCommonControls();
    ReadPreferences();
    consoleUtils(args, idk);

    const char* className = "Kill Me";

    WNDCLASSEXA wc = { 0 };
    wc.cbSize = sizeof(wc);
    wc.style = CS_CLASSDC;
    wc.lpfnWndProc = MainWindowProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInst;
    wc.hInstance = nullptr;
    wc.hCursor = LoadCursorA(hInst, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 2);
    wc.lpszMenuName = nullptr;
    wc.lpszClassName = className;
    wc.hIconSm = nullptr;

    RegisterClassExA(&wc);

    MainWindow.hWnd = CreateWindowExA(
        0,
        className, "",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 640, 480,
        nullptr, nullptr, hInst, nullptr
    );


    MainWindow.statusBar = CreateWindowExA(
        0,
        STATUSCLASSNAME,
        (PCTSTR)nullptr,
        SBARS_SIZEGRIP | WS_CHILD | WS_VISIBLE,
        0, 0, 0, 0,
        MainWindow.hWnd, (HMENU)STATUSBAR_MW_ID,
        hInst, nullptr
    );

    MainWindow.ribbon.hWnd = CreateWindowExA(
        0,
        className, "",
        WS_CHILD,
        0, 0, 0, 0,
        MainWindow.hWnd, (HMENU)1, hInst, nullptr
    );

    MainWindow.ribbon.arrowBack = CreateWindowExA(
        0,
        "buTTon", "<-",
        WS_CHILD | WS_VISIBLE,
        0, 0, 0, 0,
        MainWindow.ribbon.hWnd, (HMENU)2, hInst, nullptr
    );

    MainWindow.ribbon.arrowFwd = CreateWindowExA(
        0,
        "buTTon", "->",
        WS_CHILD | WS_VISIBLE,
        0, 0, 0, 0,
        MainWindow.ribbon.hWnd, (HMENU)2, hInst, nullptr
    );

    MainWindow.ribbon.arrowUp = CreateWindowExA(
        0,
        "buTTon", "..",
        WS_CHILD | WS_VISIBLE,
        0, 0, 0, 0,
        MainWindow.ribbon.hWnd, (HMENU)2, hInst, nullptr
    );

    MainWindow.ribbon.deleteBtn = CreateWindowExA(
        0,
        "buTTon", "Delete",
        WS_CHILD | WS_VISIBLE,
        0, 0, 0, 0,
        MainWindow.ribbon.hWnd, (HMENU)2, hInst, nullptr
    );

    MainWindow.ribbon.newFile = CreateWindowExA(
        0,
        "buTTon", "New File",
        WS_CHILD | WS_VISIBLE,
        0, 0, 0, 0,
        MainWindow.ribbon.hWnd, (HMENU)2, hInst, nullptr
    );

    SetTitToFormat(MainWindow.hWnd);
    ShowWindow(MainWindow.hWnd, SW_SHOW);
    ShowWindow(MainWindow.ribbon.hWnd, SW_SHOW);
    ShowWindow(MainWindow.ribbon.arrowBack, SW_SHOW);
    ShowWindow(MainWindow.ribbon.arrowFwd, SW_SHOW);
    ShowWindow(MainWindow.ribbon.arrowUp, SW_SHOW);
    ShowWindow(MainWindow.ribbon.deleteBtn, SW_SHOW);
    ShowWindow(MainWindow.ribbon.newFile, SW_SHOW);
    ShowWindow(MainWindow.statusBar, SW_SHOW);

    MSG msg;
    while(GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}