#include <wx/wx.h>
#include <wx/stdpaths.h>
#include <filesystem>
#include <fstream>
#include  "MainFrame.h"
#include "UserData.h"

UserPreferences UserData;


#define LINE_EQU_DEF_PATH     8
#define LINE_EQU_TIT_FORMAT   10


class StupidFiles
	:public wxApp {

private:
	std::string userPath = "";
	void readPrefFile();

public:
	virtual bool OnInit();

};

wxIMPLEMENT_APP(StupidFiles);

bool StupidFiles::OnInit() {
	{
		wxStandardPaths kkkk = wxStandardPaths::Get();
		wxString __tmpPaf = kkkk.GetUserDir(wxStandardPaths::Dir_Desktop);
		std::string _path = std::string(__tmpPaf.mb_str());

		std::filesystem::path uhh(_path);
		userPath = uhh.parent_path().string();
	}

	readPrefFile();

	wxMessageBox("Default Path:   " + UserData.DefPath + 
		"\nTitle Format:   " + UserData.TitFormat, 
		"DBug");

	// MainFrame* mainframe = new MainFrame("::This PC");
	// mainframe->Show();
	return false;
}


void StupidFiles::readPrefFile() {
	userPath += "\\s-files-prefs";
	
	std::filesystem::create_directories(userPath);
	std::string prefFile = userPath + "\\s-files-prefs.txt",
		favFile = userPath + "\\s-files-fav.txt";


	if (!std::filesystem::exists(prefFile)) {
		std::ofstream ofile(prefFile);
		ofile << "ConsoleGUI=false\n";
		ofile << "// disable GUI error reporting...\n";
		ofile << "// set it to true to enable it\n";
		ofile << "DefPath=::This PC\n";
		ofile << "// set the default path(path to open) on startup without arguements\n";
		ofile << "// set it to ::MyFavs to open favourites (if you have it)\n";
		ofile << "// OR set it to any other valid folder path\n";
		ofile << "TitFormat=Stupid File Manager\n";
		ofile << "// set the Title format for the application\n";
		ofile << "// %sf for selected file and %cp for current opened path\n";
		ofile << "SaveHistory=false\n";
		ofile << "// Not developed\n";
		ofile << "// save the history of the opened folders in s-files-history.txt\n";
		ofile << "// set it to true to enable it\n";
	}

	if (std::filesystem::exists(favFile)) {}

	std::ifstream fileToRead(prefFile);
	std::string line = "";


	while (getline(fileToRead, line)) {
		if (line != "")
			if (line.at(0) == '/' || line.at(1) == '/')
				continue;


		if (line.find("ConsoleGUI=true") == 0)
			UserData.ConsoleGUI = true;
		else if (line.find("ConsoleGUI=false") == 0)
			UserData.ConsoleGUI = false;
		else if (line.find("DefPath=") == 0) {
			UserData.DefPath = line.substr(LINE_EQU_DEF_PATH);
		}
		else if (line.find("TitFormat=") == 0) {
			UserData.TitFormat = line.substr(LINE_EQU_TIT_FORMAT);
		}
	}
}