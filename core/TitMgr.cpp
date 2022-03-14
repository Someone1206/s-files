#include "TitMgr.h"
#include "prefs.h"
#include "data.h"
#include "..\err\err.h"

// kinda doesn't work
void SetTitToFormat(HWND hWnd) {
	std::string newTit = "";

	uint32_t i = 0, len = Prefs.titFormat.length();
	char ch;
	for (; i < len; ++i) {
		ch = Prefs.titFormat.at(i);
		switch(ch) {
		case '%':
			switch(Prefs.titFormat.at(i + 1)) {
			case 's':
				switch(Prefs.titFormat.at(i + 2)) {
				case 'f':
					newTit += Data.selectedFileName;
					i += 2;
					continue;
				}
			case 'c':
				switch(Prefs.titFormat.at(i + 2)) {
				case 'p':
					newTit += Data.currentPath;
					i += 2;
					continue;
				}
			}
		}

		newTit += ch;
	}

	// alert(newTit);
	SetWindowTextA(hWnd, newTit.c_str());
	// DebugMsg();
}