#pragma once
#include <Windows.h>
#include <CommCtrl.h>

// contains structs for organisation
// of the data
// also has the IDS & constants 
// needed for MainWindow

struct MainWindowRibbon
{
    HWND hWnd,
        arrowBack,
        arrowFwd,
        arrowUp,
        deleteBtn,
        newFile;
};

struct MainWindowOrganised
{
    HWND hWnd,
        statusBar;
    MainWindowRibbon ribbon;
};

extern MainWindowOrganised MainWindow;

#define STATUSBAR_MW_ID     90
#define STATUSBAR_MW_PARTS     3
/* 
  0 -> folder info
  1 -> file info
  2 -> error info
  3 -> idk y. y not?
*/