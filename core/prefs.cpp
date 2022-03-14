#include "prefs.h"
#include <Windows.h>
#include <Shlobj.h> // Shell32.lib
#include <filesystem>
#include <fstream>
#include <iostream>
#include <limits>
#include "..\err\err.h"
#include "data.h"


UserPreferences Prefs;

#ifndef LINE_EQU_DEFPATH
#define LINE_EQU_DEFPATH 8
#endif

#ifndef LINE_EQU_TIT_FORM
#define LINE_EQU_TIT_FORM 10
#endif

void ReadPreferences() {
	Prefs.ConsoleGui = false;
	Prefs.defPath = ":ThisPc";
	Prefs.titFormat = "Stupid File Manager";

	// declare empty to prevent running into errors
	Data.currentPath = "";
	Data.selectedFileName = "";

	std::string uPath;
	{
		char path[0xffff];
		SHGetFolderPathA(nullptr, CSIDL_PROFILE, nullptr, 0, path);
		uPath = path;
	}
	uPath += "\\s-files-prefs.txt";
	std::string uhh = uPath;

	if (!std::filesystem::exists(uPath)) {
		std::ofstream fil(uPath);
		fil.close();
		return; // fill with default values
	}

	std::ifstream pref(uPath);


	while (getline(pref, uPath)) {
		if (uPath == "\n")
			continue;
		if (uPath.at(0) == '/' && uPath.at(1) == '/') // that's a comment
			continue;
		if (uPath.at(0) == '#') // that's a comment
			continue;
		if (uPath.at(0) == ';') // that's a comment
			continue;
		

		if (uPath.find("ConsoleGui=true") == 0) {
			Prefs.ConsoleGui = true;
		}
		else if (uPath.find("ConsoleGui=false") == 0) {
			Prefs.ConsoleGui = false;
		}
		else if (uPath.find("DefPath=") == 0) {
			Prefs.defPath = uPath.substr(LINE_EQU_DEFPATH);
		}
		else if (uPath.find("TitFormat=") == 0) {
			Prefs.titFormat = uPath.substr(LINE_EQU_TIT_FORM);
		}
	}

	std::cout << std::boolalpha << "Debug Info:\n" 
		<< "ConsoleGui:    \t" << Prefs.ConsoleGui
		<< "\nDefault Path:\t" << Prefs.defPath 
		<< "\nTitle format:\t" << Prefs.titFormat << std::endl;
	pref.close();
}

/***************************************
 * Title format:
 * %sf: selected file
 * %cp: current path
 ***************************************/