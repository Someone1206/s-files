#pragma once
#include <string>

// Preferences
// read preferences file on init
// and store in the struct UserPreferences

struct UserPreferences
{
	bool ConsoleGui; // want gui for console opened instance errs & msgs
	std::string defPath,
		titFormat;
};

extern UserPreferences Prefs;

void ReadPreferences();