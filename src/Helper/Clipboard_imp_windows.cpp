/*
* @Author: Pedro Henrique
* @Date:   2016-06-06 20:20:00
* @Last Modified by:   Pedro Henrique
* @Last Modified time: 2016-06-07 13:54:29
*/
#include "Clipboard_imp_windows.h"
#include "Helper/OS.h"

#ifdef _OS_WIN


#include <Windows.h>


ME::String WindowsGetClipboardData() {
	
    if (!OpenClipboard(0)) {
    	std::cout << "Win32: Failed to open clipboard" << std::endl;
        return ME::String();
    }

    HANDLE stringHandle;
    stringHandle = GetClipboardData(CF_TEXT);

    if (!stringHandle) {
        CloseClipboard();
        std::cout << "Win32: Failed to convert clipboard to string" << std::endl;
        return ME::String();
    }

    std::string stringBuffer;
    char *data = static_cast<char*>(GlobalLock(stringHandle));

	if (data == nullptr) {
		std::cout << "Win32: Failed to get the clipboard text pointer" << std::endl;
		return ME::String();
	}

    while (*data != 0) {
        stringBuffer += *data;
        data++;
    }

    ME::String result = std::string(stringBuffer);

    GlobalUnlock(stringHandle);
    CloseClipboard();

    return result;
}

void WindowsSetClipboardData(const ME::String& data) {

    HANDLE stringHandle;

    stringHandle = GlobalAlloc(GMEM_MOVEABLE, data.getString().size() + 1);

    if (!stringHandle) {
        std::cout << "Win32: Failed to allocate global handle for clipboard" << std::endl;
        return;
    }

    memcpy(GlobalLock(stringHandle), data.getString().c_str(), data.getString().size() + 1);
    GlobalUnlock(stringHandle);

    if (!OpenClipboard(0)) {
        std::cout << "Win32: Failed to open clipboard" << std::endl;
        return;
    }

    EmptyClipboard();
    SetClipboardData(CF_TEXT, stringHandle);
    CloseClipboard();
}

#else

ME::String WindowsGetClipboardData() {
    return ME::String("");
}

void WindowsSetClipboardData(const ME::String& data) {

}

#endif