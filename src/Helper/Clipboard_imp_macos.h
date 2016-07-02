#ifndef CLIPBOARD_IMP_MACOS_H
#define CLIPBOARD_IMP_MACOS_H
#include <string>
#include <iostream>
#include "Helper/String.h"


ME::String MacOSXGetClipboardData();
void MacOSXSetClipboardData(const ME::String& data);

#endif // CLIPBOARD_IMP_MACOS_H