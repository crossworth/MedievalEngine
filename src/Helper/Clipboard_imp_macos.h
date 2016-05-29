#ifndef CLIPBOARD_IMP_MACOS_H
#define CLIPBOARD_IMP_MACOS_H
#include <string>
#include <iostream>


std::string MacOSXGetClipboardData();
void MacOSXSetClipboardData(const std::string& data);

#endif // CLIPBOARD_IMP_MACOS_H