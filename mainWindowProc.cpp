#include "mainWindowProc.h"
#include "MainWindow.h"
#include "err\err.h"
#include "GUI_fns.h"
#include <iostream>


RECT globalRect;
SIZE globalSize;
PAINTSTRUCT globalPS;


LRESULT CALLBACK MainWindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch(msg) {
    case WM_DESTROY:
        PostQuitMessage(69);
        break;
    case WM_SIZE:
        {
            SendMessage(MainWindow.statusBar, WM_SIZE, 0, 0);
            GetClientRect(MainWindow.hWnd, &globalRect);

            HLOCAL hlocal = LocalAlloc(LHND, 
                sizeof(int) * STATUSBAR_MW_PARTS
            );
            PINT parts = (PINT) LocalLock(hlocal);

            parts[0] = globalRect.right / 6;
            parts[1] = parts[0] + globalRect.right / 6;
            parts[2] = parts[1] + (globalRect.right * 5 / 6);

            SendMessage(MainWindow.statusBar,
                SB_SETPARTS, (WPARAM)STATUSBAR_MW_PARTS,
                (LPARAM)parts
            );

            LocalUnlock(hlocal);
            LocalFree(hlocal);
            DebugMsgSbar(MainWindow.statusBar);

            globalSize = GetWindowSize(MainWindow.hWnd);
            // globalSize
            MoveWindow(MainWindow.ribbon.hWnd,
                0, 0, globalSize.cx, globalSize.cy / 6,
                true
            );

            globalSize = GetWindowSize(MainWindow.ribbon.hWnd);
            MoveWindow(MainWindow.ribbon.arrowBack,
                globalSize.cx / 40, globalSize.cy / 10, 
                globalSize.cx / 7, globalSize.cy * 7 / 10,
                true
            );

            GetClientRect(MainWindow.ribbon.arrowBack, &globalRect);
            MoveWindow(MainWindow.ribbon.arrowFwd,
                globalRect.right + 2 * (globalSize.cx / 40), 
                globalSize.cy / 10, 
                globalSize.cx / 7, globalSize.cy * 7 / 10,
                true
            );

            MoveWindow(MainWindow.ribbon.arrowUp,
                2 * (globalRect.right) + 3 * (globalSize.cx / 40), 
                globalSize.cy / 10, 
                globalSize.cx / 7, globalSize.cy * 7 / 10,
                true
            );

            MoveWindow(MainWindow.ribbon.deleteBtn,
                3 * (globalRect.right) + 4 * (globalSize.cx / 40), 
                globalSize.cy / 10, 
                globalSize.cx / 7, globalSize.cy * 7 / 10,
                true
            );

            MoveWindow(MainWindow.ribbon.newFile,
                4 * (globalRect.right) + 5 * (globalSize.cx / 40), 
                globalSize.cy / 10, 
                globalSize.cx / 7, globalSize.cy * 7 / 10,
                true
            );
        }
    case WM_PAINT:
        {
            HDC hdc = BeginPaint(MainWindow.ribbon.hWnd, &globalPS);
            GetClientRect(MainWindow.ribbon.hWnd, &globalRect);
            SetDCBrushColor(hdc, RGB(250, 250, 250));
            FillRect(hdc, &globalRect, (HBRUSH)GetStockObject(DC_BRUSH));
            EndPaint(MainWindow.ribbon.hWnd, &globalPS);
        }
    }

    return DefWindowProcA(hWnd, msg, wParam, lParam);
}