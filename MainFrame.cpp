#include "MainFrame.h"
#include <wx/volume.h>
#include <string>
#include <filesystem>



wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
	EVT_BUTTON(MainFrame::BTN_OPEN, MainFrame::OnOpen)
	EVT_LISTBOX(MainFrame::LIST_BOX_ALL, MainFrame::OnLBSingleClick)
wxEND_EVENT_TABLE()



MainFrame::MainFrame(wxString pathToOpen)
	:wxFrame(nullptr, wxID_ANY, "Stupid File Manager")
{
	menu_bar = new wxMenuBar;

	wxMenu* menuFile = new wxMenu;
	menuFile->Append(1, "Hello");

	menu_bar->Append(menuFile, "&File");

	SetMenuBar(menu_bar);


	__p_sizer = new wxBoxSizer(wxVERTICAL);
	paneUpper = new wxPanel(this, wxID_ANY);
	lowerSplitter = new wxSplitterWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize,
		wxSP_BORDER | wxSP_LIVE_UPDATE);
	lowerSplitter->SetMinimumPaneSize(50);
	paneLower1 = new wxPanel(lowerSplitter);
	paneLower2 = new wxPanel(lowerSplitter);

	__p_sizer->Add(paneUpper, 2, wxEXPAND);
	__p_sizer->Add(lowerSplitter, 10, wxEXPAND);

	wxBoxSizer* sizer_upper = new wxBoxSizer(wxHORIZONTAL);

	btnBack = new wxButton(paneUpper, BTN_BACK, "<-");
	btnFwd = new wxButton(paneUpper, BTN_FWD, "->");
	btnUp = new wxButton(paneUpper, BTN_UP, "..");
	btnDel = new wxButton(paneUpper, BTN_DEL, "Delete");
	btnOpen = new wxButton(paneUpper, BTN_OPEN, "Open");

	btnBack->Disable();
	btnFwd->Disable();
	btnUp->Disable();
	btnDel->Disable();
	btnOpen->Disable();

	sizer_upper->Add(btnBack, 1, wxALL, 5);
	sizer_upper->Add(btnFwd, 1, wxALL, 5);
	sizer_upper->Add(btnUp, 1, wxALL, 5);
	sizer_upper->Add(btnDel, 1, wxALL, 5);
	sizer_upper->Add(btnOpen, 1, wxALL, 5);

	paneLower1->SetBackgroundColour(wxColour(200, 200, 200));
	paneLower2->SetBackgroundColour(wxColour(250, 200, 200));

	lowerSplitter->SplitVertically(paneLower1, paneLower2, 50);
	paneUpper->SetSizerAndFit(sizer_upper);


	paneLowerSpecial = new wxPanel(paneLower2);
	// lower pane layout for special folders such as ::This PC
	paneLowerMaxUsed = new wxPanel(paneLower2);
	// lower pane layout most used (show files / folders)

	lowerPaneSizer = new wxBoxSizer(wxVERTICAL);

	wxArrayString arr = wxFSVolume::GetVolumes();


	wxGridSizer* grid = new wxGridSizer(3, 3, 0, 0);
	driveBtns = new wxButton*[arr.GetCount()];


	if (pathToOpen == "::This PC") {

		paneLowerSpecial->Show();
		paneLowerMaxUsed->Show(false);
		// ::This PC --> This PC special folder,
		// which uses the paneLowerSpecial layout


		for (uint32_t i = 0; i < grid->GetCols(); ++i) {

			driveBtns[i] = new wxButton(paneLowerSpecial, BTN_DRIVES + i, arr[i]);

			grid->Add(driveBtns[i], 1, wxEXPAND | wxALL);
			
			driveBtns[i]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, 
				&MainFrame::OnDriveButtonClicked, this);
		}

		paneLowerSpecial->SetSizerAndFit(grid);
		lowerPaneSizer->Add(paneLowerSpecial, 1, wxEXPAND);
	}
	else {
		paneLowerSpecial->Show(false);
		// not special folder then hide them
		paneLowerMaxUsed->Show();
		lowerPaneSizer->Add(paneLowerMaxUsed, 1, wxEXPAND);
	}
	
	lowerPaneMaxUsedSizer = new wxBoxSizer(wxHORIZONTAL);
	
	listOfStuffs = new wxListBox(paneLowerMaxUsed, LIST_BOX_ALL,
		wxDefaultPosition, wxDefaultSize, 0, nullptr, 
		wxLB_EXTENDED | wxLB_HSCROLL | wxLB_NEEDED_SB
	);

	lowerPaneMaxUsedSizer->Add(listOfStuffs, 1, wxEXPAND);
	paneLowerMaxUsed->SetSizerAndFit(lowerPaneMaxUsedSizer);

	paneLower2->SetSizerAndFit(lowerPaneSizer);

	this->SetSizerAndFit(__p_sizer);
	CreateStatusBar();
	SetStatusText("No Errors reported");
}


void MainFrame::OnOpen(wxCommandEvent &evt) {
	wxMessageBox("Worked!");
}

void MainFrame::OnDriveButtonClicked(wxCommandEvent &evt) {
	lowerPaneSizer->Clear();
	paneLowerSpecial->Show(false);	
	// hide it and use udder one
	paneLowerMaxUsed->Show();
	lowerPaneSizer->Add(paneLowerMaxUsed, 1, wxEXPAND | wxALL, 5);
	lowerSplitter->UpdateSize();

	int btnId = evt.GetId() - BTN_DRIVES;

	wxArrayString files;

	wxMessageBox(driveBtns[btnId]->GetLabel());

	int i = 0;
	for (const auto& dirEntry : std::filesystem::directory_iterator(
		std::string(driveBtns[btnId]->GetLabel().mb_str()))) {
		files.Add(dirEntry.path().filename().string());
	}

	btnBack->Enable();
	btnFwd->Enable();
	btnUp->Enable();
	btnOpen->Enable();
	listOfStuffs->InsertItems(files, 0);
}

void MainFrame::OnLBSingleClick(wxCommandEvent &evt) {
	btnDel->Enable();
}