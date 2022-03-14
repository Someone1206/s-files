#include "consoleUtils.h"
#include <string>
#include <Windows.h>
#include <iostream>
#include <filesystem>
#include "..\err\err.h"
#include "prefs.h"

void consoleUtils(char* args, int x) {
    std::string a = args;
    {
        int len = strlen(args);
        if (len == 0)
            return;
        if (*args == '"') args++;
        len--;
        if (*(args + len) == '"') *(args + len) = 0;
    }

    if (!std::filesystem::exists(args)) {
        if (Prefs.ConsoleGui)
            alertE(
                std::string(args) + " doesn't exist... 😶",
                std::string(args) + " is non existent"
            );
        else
            std::cout << args << " is non existent in the current storage devices of your computer\n";
    }
}