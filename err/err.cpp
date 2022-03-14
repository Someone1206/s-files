#include "err.h"
#include <Windows.h>
#include <Commctrl.h>

void alertE(std::string msg, std::string tit) {
    MessageBoxA(nullptr, msg.c_str(), tit.c_str(), MB_OK | MB_ICONERROR);
}

void alert(std::string msg, std::string tit) {
    MessageBoxA(nullptr, msg.c_str(), tit.c_str(), MB_OK | MB_ICONINFORMATION);
}



// copied and pasted from s-overflow 
// (https://stackoverflow.com/questions/1387064/how-to-get-the-error-message-from-the-error-code-returned-by-getlasterror)
//Returns the last Win32 error, in string format. Returns an empty string if there is no error.
std::string GetLastErrorAsString()
{
    //Get the error message ID, if any.
    DWORD errorMessageID = ::GetLastError();
    if(errorMessageID == 0) {
        return std::string(""); //No error message has been recorded
    }
    
    LPSTR messageBuffer = nullptr;

    //Ask Win32 to give us the string version of that message ID.
    //The parameters we pass in, tell Win32 to create the buffer that holds the message for us (because we don't yet know how long the message string will be).
    size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                                 NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);
    
    //Copy the error message into a std::string.
    std::string message(messageBuffer, size);
    
    //Free the Win32's string's buffer.
    LocalFree(messageBuffer);
            
    return message;
}

void getErrGUI() {
    std::string err = getErrMsg();
    if (err == "")
        return;
    alertE(err);
}

std::string getErrMsg() {
    return GetLastErrorAsString();
}

void DebugMsg() {
    static int errNum = 0;
    std::string err = getErrMsg();
    if (err == "") {
        alert("No error Occured!", "Debug Info");
        return;
    }
    errNum++;
    alertE(err, std::string("Error number " + std::to_string(errNum)));
}

void DebugMsgSbar(HWND sBhWnd) {
    std::string err = getErrMsg();

    if (err == "") {
        SendMessage(sBhWnd, SB_SETTEXT, 2, (LPARAM)"\tNo Errors Occurred!");
        return;
    }

    err += "\t(Error Code: " + std::to_string(GetLastError()) + ")";
    SendMessage(sBhWnd, SB_SETTEXT, 2, (LPARAM)err.c_str());
}

void SetStatusErrMsg(HWND sBhWnd, std::string err) {
    SendMessage(sBhWnd, SB_SETTEXT, 2, (LPARAM)err.c_str());
}