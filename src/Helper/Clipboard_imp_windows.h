#ifndef CLIPBOARD_IMP_WINDOWS_H_
#define CLIPBOARD_IMP_WINDOWS_H_
#include <iostream>
#include "Helper/String.h"


ME::String WindowsGetClipboardData();
void WindowsSetClipboardData(const ME::String& data);

#endif // CLIPBOARD_IMP_WINDOWS_H_