#include <string>

struct UserPreferences
{
	bool ConsoleGUI;
	std::string DefPath,
		TitFormat;
};

extern UserPreferences UserData;