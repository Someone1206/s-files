#pragma once
#include <string>

// Data
// Basic data for the current instance

struct CurrentInstanceData
{
	std::string selectedFileName,
		currentPath;
};



extern CurrentInstanceData Data;