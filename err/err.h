#pragma once
#include <string>
#include <Windows.h>

// basic error/debug reporter

// alert error
void alertE(std::string msg, std::string tit = "Error");

// normal alert
void alert(std::string msg, std::string tit = "Info");

// GetLastError converted to std::string
std::string GetLastErrorAsString();

// give a GUI err msg
void getErrGUI();

// same as GetLastErrorAsString(), just easier to type
std::string getErrMsg();

// show debug messages, inform if caught any error
void DebugMsg();

// show error message on the 3rd part of status bar
void DebugMsgSbar(HWND sBhWnd);

// set status bar error message
void SetStatusErrMsg(HWND sBhWnd, std::string err);