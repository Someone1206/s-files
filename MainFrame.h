#pragma once
#include <wx/wx.h>
#include <wx/frame.h>
#include <wx/menu.h>
#include <wx/splitter.h>


class MainFrame :
    public wxFrame
{
private:
    wxMenuBar* menu_bar = nullptr;

    wxBoxSizer* __p_sizer = nullptr;
    wxPanel* paneUpper = nullptr, 
        * paneLower1 = nullptr,
        * paneLower2 = nullptr;

    wxPanel* paneLowerSpecial = nullptr,
        * paneLowerMaxUsed = nullptr;

    wxSplitterWindow* lowerSplitter = nullptr;

    wxButton* btnBack = nullptr,
        * btnFwd = nullptr,
        * btnUp = nullptr,
        * btnDel = nullptr,
        * btnOpen = nullptr;

    wxButton** driveBtns = nullptr;

    wxBoxSizer* lowerPaneSizer = nullptr,
        * lowerPaneMaxUsedSizer = nullptr;

    wxListBox* listOfStuffs = nullptr;

    wxDECLARE_EVENT_TABLE();

public:
    MainFrame(wxString pathToOpen);
    




    enum {
        BTN_BACK,
        BTN_FWD,
        BTN_UP,
        BTN_DEL,
        BTN_OPEN,

        BTN_DRIVES,

        LIST_BOX_ALL
    };




    void OnOpen(wxCommandEvent &evt);

    void OnDriveButtonClicked(wxCommandEvent &evt);

    void OnLBSingleClick(wxCommandEvent &evt);
};
